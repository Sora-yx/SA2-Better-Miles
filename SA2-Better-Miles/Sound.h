#pragma once

#define Status_KillSound 0x4000


void Sounds_Init(const HelperFunctions& helperFunctions, const IniFile* config);
void RunCustomSounds();
DWORD LoadSoundSteam_LoadFromFile(std::string path);
void ResumeCustomSounds();
void PauseCustomSounds();
void FreeAllCustomSounds();

void PlayCustomSound(int ID);
void PlayCustomSoundVolume(int ID, float volume);
void PlayDelayedCustomSound(int ID, int time, float volumeoverride);
void PlayCustomSound_EntityOnlyOneAllowed(int ID, ObjectMaster* obj, float dist, bool loop);
void PlayCustomSound_Entity(int ID, ObjectMaster* obj, float dist, bool loop);
void PlayCustomSound_EntityAndPos(int ID, ObjectMaster* obj, NJS_VECTOR* pos, float dist, float volume, bool loop);
void PlayCustomSound_EntityAndVolume(int ID, ObjectMaster* obj, float dist, float volume, bool loop);
void PlayCustomSound_Pos(int ID, NJS_VECTOR* pos, float dist, float volume, bool loop);

enum CM_SoundList {
	SE_tornado_Transfo01 = 1000,
	SE_tornado_Transfo02,
	SE_tornado_Transfo03,
	SE_tornadoTransfoFinish,
	SE_tornadoFlying = 1010,
	SE_tornadoBoost,
	Voice_TailsTimeToJam = 2000,
	Voice_TailsLetsDoIt,
	Voice_TailsWow,
	Voice_TailsYay,
	Voice_TailsTired,
};
