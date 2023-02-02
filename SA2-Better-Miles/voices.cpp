#include "pch.h"

static UsercallFuncVoid(PlayIdle_Voice_t, (CharObj2Base* a1, char a2), (a1, a2), 0x477BB0, rEAX, stack4);

void PlayIdle_Voice_r(CharObj2Base* co2, char a2)
{
	if (!co2 || co2->CharID2 != Characters_Tails)
	{
		return PlayIdle_Voice_t.Original(co2, a2);
	}

	if (co2->PlayerNum != 0 || TwoPlayerMode || CurrentLevel == LevelIDs_ChaoWorld)
		return;

	int charID2 = co2->CharID2;

	if (charID2 == Characters_Tails) 
	{
		charID2 = Characters_MechTails;
	}

	__int16 voiceID = 0;

	Float v9 = (Float)rand() * 0.000030517578125f;
	if (v9 <= 0.5f)
	{
		char v7 = byte_1738C69;
		char* v8 = (char*)0x1738C68;

		if (byte_1738C69 == 91)
		{
			return;
		}
		while (v7 != CurrentLevel || *v8 != charID2)
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
			voiceID = *((WORD*)v8 + 1);
		}
		else
		{
			voiceID = *((WORD*)v8 + 2);
		}
	}
	else
	{
		short* v4 = &word_1738D58;
		if (*(__int16*)0x1738D58 == -1)
		{
			return;
		}
		int v5 = word_1738D58;
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
			voiceID = v4[2];
		}
		else
		{
			voiceID = v4[1];
		}
	}
	if (voiceID != -1)
	{
		PlayVoice(2, voiceID);
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

	PlayIdle_Voice_t.Hook(PlayIdle_Voice_r);
}