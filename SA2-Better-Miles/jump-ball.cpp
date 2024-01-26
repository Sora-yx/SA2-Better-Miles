#include "pch.h"

std::shared_ptr<ModelInfo> JumpBallMdl;
std::shared_ptr<ModelInfo> JumpBallShadowMdl;

NJS_TEXNAME MilesBallTex[2];

NJS_TEXLIST MilesBall_Texlist = { arrayptrandlength(MilesBallTex) };
NJS_TEXLIST MilesBall1_Texlist = { arrayptrandlength(MilesBallTex) };

int spinTimer = 0;

static UsercallFunc(signed int, Tails_JumpStart_t, (CharObj2Base* a1, EntityData1* a2), (a1, a2), 0x751B80, rEAX, rEAX, rECX);

void Miles_SetJmpBall(TailsCharObj2* mco2) 
{
	if (!isJumpBall)
		return;

	if (!isSA1Char(Characters_Tails)) 
	{
		CharacterModels[jmpBallID].Model = JumpBallMdl->getmodel();
	}

	LoadTextureList("ballTex", &MilesBall1_Texlist);
	return;
}

void DrawMiles_JumpBall(NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) {

	if (MilesCO2Extern && JumpBallMdl != nullptr) 
	{

		char pID = MilesCO2Extern->base.PlayerNum;
		EntityData1* data1 = MainCharObj1[pID];
		TailsCharObj2* mCO2 = MilesCO2Extern;
		NJS_VECTOR scale = { 0.9f, 0.9f, 0.9f };

		AnimationIndex* sa2anim = getCharAnim_r();

		int curAnim = mCO2->base.AnimInfo.Current;

		if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0 && mCO2->base.AnimInfo.mtnmode != 2)
		{
			mdl = CharacterModels[jmpBallID].Model;

			if (!isSA1Char(Characters_Tails)) 
			{
				njSetTexture(&MilesBall1_Texlist);
			}

			njScaleV_(&scale);
			curAnim = 30;

			if (sa2anim)
			{
				motion = sa2anim[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
			}
			else 
			{
				motion = CharacterAnimations[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
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

int Tails_JumpStart_r(CharObj2Base* co2, EntityData1* data)
{
	signed int result = Tails_JumpStart_t.Original(co2, data);

	if (result == 1 && data->Action == Action_Jump && (co2->SurfaceInfo.PrevTopSurface & (SurfaceFlag_WaterNoAlpha | SurfaceFlag_Water)) == 0) {
		{
			data->Status |= Status_Ball;
		}
	}

	return result;
}

void DrawMiles_JumpBallShadow(NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) 
{

	if (MilesCO2Extern && JumpBallShadowMdl != nullptr)
	{
		char pID = MilesCO2Extern->base.PlayerNum;
		EntityData1* data1 = MainCharObj1[pID];
		TailsCharObj2* mCO2 = MilesCO2Extern;
		NJS_VECTOR scale = { 0.9f, 0.9f, 0.9f };

		AnimationIndex* sa2anim = getCharAnim_r();

		int curAnim = mCO2->base.AnimInfo.Current;

		if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0 && mCO2->base.AnimInfo.mtnmode != 2)
		{
			mdl = JumpBallShadowMdl->getmodel();

			if (!isSA1Char(Characters_Tails))
			{
				njSetTexture(&MilesBall1_Texlist);
			}

			njScaleV_(&scale);
			curAnim = 30;

			if (sa2anim)
			{
				motion = sa2anim[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
			}
			else
			{
				motion = CharacterAnimations[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
			}
		}
	}

	return DrawMotionAndObject(motion, mdl, frame);
}

static void __declspec(naked) DrawMilesJumpBall_ShadowASM()
{
	__asm
	{
		push[esp + 08h] // frame
		push[esp + 08h] // obj
		push ecx // mtn
		call DrawMiles_JumpBallShadow
		pop ecx // mtn
		add esp, 4 // obj
		add esp, 4 // frame
		retn
	}
}

void Init_JumpBallhack() {

	if (!isJumpBall)
		return;

	WriteCall((void*)0x750ABF, DrawMotionAndObject_Hack);
	WriteCall((void*)0x750196, DrawMilesJumpBall_ShadowASM);

	Tails_JumpStart_t.Hook(Tails_JumpStart_r);
	JumpBallMdl = LoadMDLSmartPtr("230", ModelFormat_Chunk);
	JumpBallShadowMdl = LoadMDLSmartPtr("230_shadow", ModelFormat_Chunk);
	return;
}