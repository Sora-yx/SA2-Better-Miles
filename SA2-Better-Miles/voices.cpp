#include "pch.h"

Trampoline* PlayIdle_Voice_t;

static inline void PlayIdle_Voice_origin(CharObj2Base* co2, char a2)
{
	const auto target = PlayIdle_Voice_t->Target();

	__asm
	{
		push[a2]
		mov eax, [co2]
		call target
		add esp, 4
	}
}


void PlayIdle_Voice_r(CharObj2Base* co2, char a2)
{
	int charID2; // ebx
	int curLevel; // edi
	__int16* v4; // ecx
	__int16 v5; // ax
	__int16 v6; // ax
	char v7; // al
	char* v8; // esi
	float v9; // [esp+0h] [ebp-4h]

	charID2 = co2->CharID2;

	if (charID2 == Characters_Tails) 
	{
		charID2 = Characters_MechTails;
	}
	else 
	{
		return PlayIdle_Voice_origin(co2, a2);
	}

	curLevel = CurrentLevel;

	if (co2->PlayerNum != 0 || TwoPlayerMode  || CurrentLevel == LevelIDs_ChaoWorld)
		return;

	v9 = (double)rand() * 0.000030517578125;
	if (v9 <= 0.5)
	{
		v7 = byte_1738C69;
		v8 = (char*)0x1738C68;
		if (byte_1738C69 == 91)
		{
			return;
		}
		while (v7 != curLevel || *v8 != charID2)
		{
			v7 = v8[7];
			v8 += 6;
			if (v7 == 91)
			{
				return;
			}
		}
		if (((int)(v9 * (double)(unsigned int)FrameCountIngame) & 1) != 0)
		{
			v6 = *((WORD*)v8 + 1);
		}
		else
		{
			v6 = *((WORD*)v8 + 2);
		}
	}
	else
	{
		v4 = &word_1738D58;
		if (*(__int16*)0x1738D58 == -1)
		{
			return;
		}
		v5 = word_1738D58;
		while (v5 != charID2)
		{
			v5 = v4[3];
			v4 += 3;
			if (v5 == -1)
			{
				return;
			}
		}
		if ((a2 & 1) != 0)
		{
			v6 = v4[2];
		}
		else
		{
			v6 = v4[1];
		}
	}
	if (v6 != -1)
	{
		PlayVoice(2, v6);
	}
}

static void __declspec(naked) PlayIdle_VoiceASM()
{
	__asm
	{
		push[esp + 04h] // a2
		push eax // co2

		// Call your __cdecl function here:
		call PlayIdle_Voice_r

		pop eax // co2
		add esp, 4 // a2
		retn
	}
}


void PlayRankVoice_i(int id)
{
	int v23 = -1;
	switch (id)
	{
	case Characters_Sonic:
	case Characters_SuperSonic:
		v23 = SonicRankVoices[CurrentLevelRank];
		break;
	case Characters_Shadow:
	case Characters_SuperShadow:
		v23 = ShadowRankVoices[CurrentLevelRank];
		break;
	case Characters_Knuckles:
		v23 = KnucklesRankVoices[CurrentLevelRank];
		break;
	case Characters_Rouge:
		v23 = RougeRankVoices[CurrentLevelRank];
		break;
	case Characters_Tails:
	case Characters_MechTails:
		v23 = TailsRankVoices[CurrentLevelRank];
		break;
	case Characters_Eggman:
	case Characters_MechEggman:
		v23 = EggmanRankVoices[CurrentLevelRank];
		break;
	}
	if (v23 != -1)
	{
		PlayVoice(2, v23);
	}
}

const void* const loc_44FD08 = (void*)0x44FD08;
__declspec(naked) void PlayRankVoice()
{
	__asm
	{
		push eax
		call PlayRankVoice_i
		add esp, 4
		jmp loc_44FD08
	}
}

void Init_VoicesFixes() {

	if (!isCharaSelect())
		WriteJump((void*)0x44FC5E, PlayRankVoice);

	if (!jumpVoice) {
		WriteData<5>((void*)0x751C90, 0x90); //remove tails voice when jumping
		WriteData<5>((void*)0x751BFA, 0x90);
	}

	PlayIdle_Voice_t = new Trampoline((int)0x477BB0, (int)0x477BB5, PlayIdle_VoiceASM);

	return;
}