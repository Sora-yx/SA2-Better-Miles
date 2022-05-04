#include "pch.h"

ModelInfo* JumpBallMdl = nullptr;

NJS_TEXNAME MilesBallTex[2];

NJS_TEXLIST MilesBall_Texlist = { arrayptrandlength(MilesBallTex) };

NJS_TEXLIST MilesBall1_Texlist = { arrayptrandlength(MilesBallTex) };

int spinTimer = 0;

Trampoline* Tails_JumpStart_t = nullptr;

void Miles_LoadJmpBall(TailsCharObj2* mco2) {

	if (!isSA1Char(Characters_Tails)) {
		JumpBallMdl = LoadMDL("230", ModelFormat_Chunk);
		CharacterModels[jmpBallID].Model = JumpBallMdl->getmodel();
	}

	LoadTextureList("ballTex", &MilesBall1_Texlist);
	return;
}

void DrawMiles_JumpBall(NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) {

	if (MilesCO2Extern) {

		char pID = MilesCO2Extern->base.PlayerNum;
		EntityData1* data1 = MainCharObj1[pID];
		TailsCharObj2* mCO2 = MilesCO2Extern;
		NJS_VECTOR scale = { 0.9f, 0.9f, 0.9f };

		AnimationIndex* sa2anim = getCharAnim_r();

		int curAnim = mCO2->base.AnimInfo.Current;

		if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0 && mCO2->base.AnimInfo.AnimationFrame != 2)
		{
			mdl = CharacterModels[jmpBallID].Model;

			if (!isSA1Char(Characters_Tails)) {
				njSetTexture(&MilesBall1_Texlist);
			}

			njScaleV_(&scale);
			curAnim = 30;

			if (sa2anim)
			{
				motion = sa2anim[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
			}
			else {
				motion = CharacterAnimations[mCO2->base.AnimInfo.Animations[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].AnimNum].Animation;
			}
		}
	}

	return DrawMotionAndObject(motion, mdl, frame);
}

static void __declspec(naked) DrawMotionAndObject_Hack()
{
	__asm
	{
		push[esp + 08h] // frame
		push[esp + 08h] // obj
		push ecx // mtn

		call DrawMiles_JumpBall

		pop ecx // mtn
		add esp, 4 // obj
		add esp, 4 // frame
		retn
	}
}

static inline signed int Tails_JumpStart_Origin(CharObj2Base* co2, EntityData1* data)
{
	const auto target = Tails_JumpStart_t->Target();
	signed int result;

	__asm
	{
		mov ecx, [data]
		mov eax, [co2]
		call target
		mov result, eax
	}

	return result;
}


int Tails_JumpStart_r(CharObj2Base* co2, EntityData1* data)
{
	signed int result = Tails_JumpStart_Origin(co2, data);

	if (result == 1 && data->Action == Action_Jump)
	{
		data->Status |= Status_Ball;
	}

	return result;
}

static void __declspec(naked) Tails_JumpStartASM()
{
	__asm
	{
		push ecx 
		push eax 
		call Tails_JumpStart_r
		add esp, 4 
		pop ecx
		retn
	}
}


void Init_JumpBallhack() {

	if (!isJumpBall)
		return;

	WriteCall((void*)0x750ABF, DrawMotionAndObject_Hack);

	Tails_JumpStart_t = new Trampoline((int)0x751B80, (int)0x751B85, Tails_JumpStartASM);
	return;
}