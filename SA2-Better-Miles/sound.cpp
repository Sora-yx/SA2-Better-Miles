#include "pch.h"
#include "bass_vgmstream.h"

typedef struct {
	int				id;
	float			dist;
	float			volumeA;
	float			volumeB;
	float			pitch;
	NJS_VECTOR* position;
	HSTREAM			stream;
	ObjectMaster* obj;
} CUSTOM_SOUNDENTRY;

static CUSTOM_SOUNDENTRY SoundListEntries[256];

static bool SoundDevice;

void PauseCustomSounds() {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		BASS_ChannelPause(SoundListEntries[i].stream);
	}
}

void ResumeCustomSounds() {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		BASS_ChannelPlay(SoundListEntries[i].stream, false);
	}
}

int GetFreeSoundEntry() {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		if (SoundListEntries[i].stream == NULL) {
			SoundListEntries[i].dist = 0;
			SoundListEntries[i].obj = nullptr;
			SoundListEntries[i].pitch = 0;
			SoundListEntries[i].volumeA = 0.4f;
			SoundListEntries[i].volumeB = 0;
			SoundListEntries[i].position = NULL;
			return i;
		}
	}

	return -1;
}

int GetSoundEntryByStream(HCHANNEL channel) {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		if (SoundListEntries[i].stream == channel) return i;
	}

	return -1;
}

static void __stdcall FreeSoundStream(HSYNC handle, DWORD channel, DWORD data, void* user)
{
	BASS_ChannelStop(channel);
	BASS_StreamFree(channel);
}

static void __stdcall FreeSoundStreamQueue(HSYNC handle, DWORD channel, DWORD data, void* user)
{
	int entryID = GetSoundEntryByStream(channel);

	if (entryID > -1) {
		SoundListEntries[entryID].stream = NULL;
	}

	FreeSoundStream(handle, channel, data, user);
}

void FreeAllCustomSounds() {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		FreeSoundStream(NULL, SoundListEntries[i].stream, NULL, NULL);
		SoundListEntries[i].stream = NULL;
		SoundListEntries[i].dist = 0;
		SoundListEntries[i].obj = nullptr;
		SoundListEntries[i].pitch = 0;
		SoundListEntries[i].volumeA = 0.4f;
		SoundListEntries[i].volumeB = 0;
		SoundListEntries[i].position = NULL;
	}
}

DWORD LoadSoundSteam_LoadFromFile(std::string path) {
	const char* filename = HelperFunctionsGlobal.GetReplaceablePath(path.c_str());

	DWORD channel = BASS_VGMSTREAM_StreamCreate(filename, 0);

	if (channel == 0)
	{
		channel = BASS_StreamCreateFile(false, filename, 0, 0, 0);
	}

	return channel;
}

DWORD LoadSoundStream(int ID) {
	const char* filename = "resource\\gd_PC\\Sounds\\";
	std::string str1 = filename + std::to_string(ID) + ".wav";
	std::string str2 = filename + std::to_string(ID) + ".adx";

	DWORD channel = LoadSoundSteam_LoadFromFile(str1);

	if (channel == 0) {
		channel = LoadSoundSteam_LoadFromFile(str2);
	}

	return channel;
}

float GetVolumeRange(NJS_VECTOR* pos, float dist) {

	float playerdist = CheckDistance(&CameraData.Position, pos);
	return 0.4 - (0.4 * playerdist / dist);

}

void PlaySoundChannelQueue(int ID, int entryID, bool loop) {
	HSTREAM channel = LoadSoundStream(ID);

	if (channel != 0)
	{
		BASS_ChannelPlay(channel, false);
		BASS_ChannelSetAttribute(channel, BASS_ATTRIB_VOL, SoundListEntries[entryID].volumeA);

		if (loop) {
			BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
		}
		else {
			BASS_ChannelSetSync(channel, BASS_SYNC_END, 0, FreeSoundStreamQueue, nullptr);
		}

		SoundListEntries[entryID].id = ID;
		SoundListEntries[entryID].stream = channel;
	}
}

void PlayCustomSound(int ID) {
	int entryID = GetFreeSoundEntry();

	if (entryID > -1) {
		PlaySoundChannelQueue(ID, entryID, 0);
	}
}

void PlayCustomSoundVolume(int ID, float volume) {
	int entryID = GetFreeSoundEntry();

	if (entryID > -1) {
		SoundListEntries[entryID].volumeB = volume;
		PlaySoundChannelQueue(ID, entryID, 0);
	}
}

void PlayCustomSoundQueue(int ID, ObjectMaster* obj, NJS_VECTOR* pos, float dist, bool loop, float volume, float pitch) {
	int entryID = GetFreeSoundEntry();

	if (entryID > -1) {
		SoundListEntries[entryID].obj = obj;
		SoundListEntries[entryID].dist = dist;

		//The first frame is always wrong for 3d volume, skip it
		if (obj || pos) SoundListEntries[entryID].volumeA = 0;

		if (volume) SoundListEntries[entryID].volumeB = volume;
		if (pitch) SoundListEntries[entryID].pitch = pitch;
		if (pos) SoundListEntries[entryID].position = pos;

		PlaySoundChannelQueue(ID, entryID, loop);
	}
}

void PlayCustomSound_Entity(int ID, ObjectMaster* obj, float dist, bool loop) {
	dist *= 2;
	PlayCustomSoundQueue(ID, obj, NULL, dist, loop, NULL, NULL);
}

void PlayCustomSound_EntityOnlyOneAllowed(int ID, ObjectMaster* obj, float dist, bool loop) {
	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		if (SoundListEntries[i].obj && SoundListEntries[i].obj->MainSub == obj->MainSub) {
			if (IsPlayerInsideSphere(&SoundListEntries[i].obj->Data1.Entity->Position, SoundListEntries[i].dist * 2)) {
				return;
			}
		}
	}

	PlayCustomSound_Entity(ID, obj, dist, loop);
}

void PlayCustomSound_EntityAndVolume(int ID, ObjectMaster* obj, float dist, float volume, bool loop) {
	dist *= 2;
	PlayCustomSoundQueue(ID, obj, NULL, dist, loop, volume, NULL);
}

void PlayCustomSound_EntityAndPos(int ID, ObjectMaster* obj, NJS_VECTOR* pos, float dist, float volume, bool loop) {
	PlayCustomSoundQueue(ID, obj, pos, dist, loop, volume, NULL);
}

void PlayCustomSound_Pos(int ID, NJS_VECTOR* pos, float dist, float volume, bool loop) {
	PlayCustomSoundQueue(ID, nullptr, pos, dist, loop, volume, NULL);
}

void DelayedCustomSound(ObjectMaster* obj) {
	if (--obj->Data1.Entity->Scale.y <= 0) {
		if (obj->Data1.Entity->Scale.z != 0) {
			PlayCustomSoundVolume(obj->Data1.Entity->Scale.x, obj->Data1.Entity->Scale.z);
		}
		else {
			PlayCustomSound(obj->Data1.Entity->Scale.x);
		}

		DeleteObject_(obj);
	}
}

void PlayDelayedCustomSound(int ID, int time, float volumeoverride) {
	ObjectMaster* temp = LoadObject(1, "DelayedCustomSound", DelayedCustomSound, LoadObj_Data1);
	temp->Data1.Entity->Scale.x = ID;
	temp->Data1.Entity->Scale.y = time;
	temp->Data1.Entity->Scale.z = volumeoverride;
}

void RunCustomSounds() {
	if (GameState < GameStates_Ingame || GameState > GameStates_Pause)
		return;

	for (int i = 0; i < LengthOfArray(SoundListEntries); ++i) {
		if (SoundListEntries[i].stream != NULL) {
			HSTREAM stream = SoundListEntries[i].stream;

			// Ignore if the sound is paused
			if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_PAUSED) {
				continue;
			}

			if (BASS_ChannelIsActive(stream) == BASS_ACTIVE_STOPPED ||
				BASS_ChannelIsActive(stream) == BASS_ACTIVE_STALLED) {
				FreeSoundStreamQueue(NULL, stream, NULL, NULL);
			}

			if (SoundListEntries[i].obj && (!SoundListEntries[i].obj->Data1.Entity || SoundListEntries[i].obj->Data1.Entity->Status & Status_KillSound)) {
				FreeSoundStreamQueue(NULL, stream, NULL, NULL);
				SoundListEntries[i].stream = NULL;
				continue;
			}

			// Get the volume of the sound based on the distance from the entity or the static position
			if (SoundListEntries[i].dist > 0) {
				if (SoundListEntries[i].position) {
					if (!IsPlayerInsideSphere(SoundListEntries[i].position, SoundListEntries[i].dist)) {
						SoundListEntries[i].volumeA = 0;
					}
					else {
						SoundListEntries[i].volumeA = GetVolumeRange(SoundListEntries[i].position, SoundListEntries[i].dist);
					}
				}
				else {
					if (!IsPlayerInsideSphere(&SoundListEntries[i].obj->Data1.Entity->Position, SoundListEntries[i].dist)) {
						SoundListEntries[i].volumeA = 0;
					}
					else {
						SoundListEntries[i].volumeA = GetVolumeRange(&SoundListEntries[i].obj->Data1.Entity->Position, SoundListEntries[i].dist);
					}
				}

				// If volume B is set (static volume), multiply Volume A (3d volume here) by it.
				if (SoundListEntries[i].volumeB) {
					SoundListEntries[i].volumeA *= SoundListEntries[i].volumeB;
				}

				// Set the new volume
				BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, SoundListEntries[i].volumeA);
			}
			else if (SoundListEntries[i].volumeB) {
				// If the sound is not 3d and Volume B is set (static volume), set it.
				BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, SoundListEntries[i].volumeB);
			}
		}
	}
}

VoidFunc(sub_443290, 0x443290);
void ResumeSound_j() {
	sub_443290();
	ResumeCustomSounds();
}


VoidFunc(sub_443250, 0x443250);

void PauseSound_j() {
	sub_443250();
	PauseCustomSounds();
}

void init_BassSound() {
	WriteCall((void*)0x43602C, PauseSound_j);
	WriteCall((void*)0x436071, ResumeSound_j);
	return;
}