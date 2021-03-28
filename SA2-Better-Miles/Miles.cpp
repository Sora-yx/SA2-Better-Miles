#include "stdafx.h"
#include <fstream>
#include <iostream>

Trampoline* Tails_Main_t;
Trampoline* Miles_CheckNextActions_t;
Trampoline* Tails_RunsAction_t;
Trampoline* LoadCharacters_t;

//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.
static const void* const Miles_CheckNextActionPtr = (void*)0x751CB0;
signed int Miles_CheckNextActions_original(EntityData2_R* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {
	const auto MilesCheck_ptr = Miles_CheckNextActions_t->Target();

	signed int result;

	__asm
	{
		mov esi, a4 // a4
		mov edi, a3 // a3
		mov ebx, a2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call MilesCheck_ptr

		mov result, eax
	}

	return result;
}

signed int __cdecl Miles_CheckNextActions_r(EntityData2_R* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {
	switch (a4->NextAction)
	{
	case 1:
		if (CurrentLevel == LevelIDs_RadicalHighway)
			a4->Action = 1; //fix softlock last loop
		else
			a4->Action = 2;
		break;
	case 3:
		if (a4->Action == Rolling)
		{
			a4->Action = 1;
			a3->AnimInfo.Next = 1;
			a4->Status &= 0xFAFFu;
			return 1;
		}
		if (a4->Action != 71)
		{
			return 1;
		}
		a4->Action = 10;
		a3->AnimInfo.Next = 15;
		a4->Status &= 0xDFFFu;
		return 1;
	case 20: //Pulley
		a4->Status &= 0xDAFFu;
		a3->Speed = { 0, 0, 0 };
		a4->Action = Pulley;
		a3->AnimInfo.Next = 75;
		return 1;
	case 28:
		a4->Action = 56;
		a4->Status &= 0xDAFFu;
		return 1;
	case 31:
		if (setGrindingNextAction(a2, a3, a4))
			return 1;
		else
			return 0;
	case 32:
		if (!CharacterAnimations[200].Animation)
		{
			return 1;
		}
		if (SetHandGranding(a1, a3, a4))
		{
			return 1;
		}
		return 0;
	case 34: //snowboard stuff
		a4->Action = 79;
		a3->AnimInfo.Next = 129; //board
		if ((a4->Status & 0x100) != 0)
		{
			a4->Status &= 0xFEFFu;
		}
		a4->Status &= 0xDFFFu;
		//*(float*)&a3->field_2C[16] = 0.0;
		return 1;
	case 38:
		a4->Action = 6;
		return 1;
	case 39:
		a4->Action = Spinning;
		a3->AnimInfo.field_8 = 0;
		a3->AnimInfo.Current = 94;
		Play3DSound_Pos(8200, &a4->Position, 0, 0, 0);
		return 1;
	case 102:
		MainCharObj1[0]->field_2 = 1;
		a4->NextAction = 0;
		return 0;
	case 103:
		Miles_PerformLightDash(a3, a4);
		return 1;
	}

	return Miles_CheckNextActions_original(a1, a2, a3, a4);
}

static void __declspec(naked) Miles_CheckNextActionsASM()
{
	__asm
	{
		push esi // a4
		push edi // a3
		push ebx // a2
		push ecx // a1

		// Call your __cdecl function here:
		call Miles_CheckNextActions_r

		pop ecx // a1
		pop ebx // a2
		pop edi // a3
		pop esi // a4
		retn
	}
}

static inline signed int Tails_CheckActionWindowASM(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3, TailsCharObj2* a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov ecx, [a3]
		mov edx, [a2]
		mov eax, [a1]
		call Tails_CheckActionWindowPtr
		add esp, 4
		mov result, eax
	}
	return result;
}

signed int Tails_CheckActionWindowR(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3, TailsCharObj2* a4) {
	return Tails_CheckActionWindowASM(a1, a2, a3, a4);
}

int ActionArray[6] = { Jumping, 24, ObjectControl, Pulley, 66, VictoryPose };

//Edit the function which checks where it needs to animate Miles's tails to add more actions.
static const void* const loc_7512F2 = (void*)0x7512F2;
__declspec(naked) void  CheckAnimateTailsAction() {
	for (int i = 0; i < LengthOfArray(ActionArray); i++)
	{
		if (MainCharObj1[0]->Action != ActionArray[i])
		{
			_asm jmp loc_7512F2
			break;
		}
	}
}

void Miles_DoCollisionAttackStuff(EntityData1* data1) {
	data1->Status |= Status_Attack;
	data1->Collision->CollisionArray[0].damage &= 0xFCu;
	data1->Collision->CollisionArray[0].damage |= 0xCu;
	data1->Collision->CollisionArray[0].damage |= 0xEF;
	data1->Collision->CollisionArray[1].center = data1->Position;
	data1->Collision->CollisionArray[1].attr &= 0xFFFFFFEF;
	return;
}

static const void* const TailsJumpPtr = (void*)0x751B80;
static inline int Tails_JumpStart(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		mov ecx, [a2]
		mov eax, [a1]
		call TailsJumpPtr
		mov result, eax
	}

	return result;
}

int CheckTailsJump(CharObj2Base* a1, EntityData1* a2)
{
	return Tails_JumpStart(a1, a2);
}

void Miles_DrawTail(NJS_OBJECT* Tail, int(__cdecl* callback)(NJS_CNK_MODEL*)) {
	if (MainCharObj1[0]->Action != Rolling)
		ProcessChunkModelsWithCallback(Tail, ProcessChunkModel);
}



void __cdecl Tails_runsAction_r(EntityData1* data1, EntityData2_R* data2, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	FunctionPointer(void, original, (EntityData1 * data1, EntityData2_R * data2, CharObj2Base * co2, TailsCharObj2 * co2Miles), Tails_RunsAction_t->Target());
	original(data1, data2, co2, co2Miles);


	switch (data1->Action)
	{
	case Standing:
	case Running:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case Jumping:
		if (Miles_CheckBounceAttack(co2, data1) || Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case 7:
	case 8:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case 10:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		*(int*)&co2Miles->field_1BC[436] = -17000;
		
		break;
	case 15:
	case 17:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case MysticMelody:
		if (Miles_CheckNextActions_r(data2, co2Miles, co2, data1)) {
			return;
		}

		if ((co2->AnimInfo.field_C & 1) != 0)
		{
			data1->Action = 0;
		}
		return;
	case Pulley:
		if (!Miles_CheckNextActions_r(data2, co2Miles, co2, data1)) {
			CheckTailsJump(co2, data1);
		}
		return;
	case Action_AirBubble:
		*(int*)&co2Miles->field_1BC[436] = -17000;
		break;
	case Flying:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		if (isSuperForm() && co2->AnimInfo.Next == 92 || co2->AnimInfo.Current == 92)
		{
			co2->AnimInfo.Next = 15;
		}
		break;
	case Spinning:
		if (Miles_CheckNextActions_r(data2, co2Miles, co2, data1) || Miles_SetNextActionSwim(co2Miles, data1))
			return;

		if (isCustomAnim)
			spinOnFrames(co2, data1);

		break;
	case Bounce:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		DoBounce(data1, co2, co2Miles, data2);
		break;
	case BounceFloor:

		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		DoBounceOnFloor(data1, co2, co2Miles, data2);
		break;
	case Grinding:
		if (Miles_CheckNextActions_r(data2, co2Miles, co2, data1))
			return;

		CheckGrindThing(data1, data2, co2, co2Miles);
		break;
	case HandGrinding: //Or whatever you call that thing in CG
		DoHangGrinding(data1, co2);
		return;
	case 76:
		BoardStuff(data2, co2Miles, data1, co2);
		return;
	case 79:
		if ((data1->Status & 3) == 0)
		{
			return;
		}

		PlaySoundProbably(8195, 0, 0, 0);
		data1->Action = 76;
		co2->AnimInfo.Next = 121;
		co2->AnimInfo.field_10 = 0.0;
		if (co2->Speed.x <= 0.30000001)
		{
			co2->Speed.x = 1.0;
		}
		data1->Rotation.x = data2->ang_aim.x;
		data1->Rotation.z = data2->ang_aim.z;
		break;
	case 80:
		BoardJumpStuff(data1, co2, data2);
		break;
	case Rolling:
		if (Miles_CheckNextActions_r(data2, co2Miles, co2, data1))
			return;

		Miles_UnrollCheck(data1, data2, co2);
		return;
	case LightDash:
		CheckLightDashEnd(co2Miles, co2, data1);
		return;
	case FloatingOnWater:
		CheckFloatingStuff(data2, data1, co2, co2Miles);
		break;
	case Swimming:
		*(int*)&co2Miles->field_1BC[436] = -17000; //fix "rotation Y" of the tails
		CheckSwimmingStuff(data2, data1, co2, co2Miles);
		break;
	case Diving:
		*(int*)&co2Miles->field_1BC[436] = -17000;
		CheckDivingStuff(data2, data1, co2, co2Miles);
		break;
	}
}

void Tails_Main_r(ObjectMaster* obj)
{

	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2_R* data2 = EntityData2Ptrs[0];
	TailsCharObj2* co2Miles = (TailsCharObj2*)MainCharObj2[0];

	switch (data1->Action)
	{
	case Standing:
	case Running:

		if (!Miles_CheckNextActions_r(data2, co2Miles, co2, data1) && !CheckTailsJump(co2, data1)) {
			if (co2->Speed.x < 1.3) {
				Miles_CheckSpinAttack(co2Miles, data1, co2, data2);
			}
			else {
				Miles_RollCheckInput(data1, co2);
			}
		}
		break;
	case Jumping:
		Miles_DoCollisionAttackStuff(data1);
		break;
	case ObjectControl:
		if (!isCustomAnim)
			break;

		if (TimerStopped != 0 && (co2->AnimInfo.Next == 54 || co2->AnimInfo.Current == 54)) { //Check if the level is finished
			if (isSuperForm()) {
				co2->AnimInfo.Next = VictorySuperForm;
			}
			else {
				co2->AnimInfo.Next = VictoryAnim;
			}
			data1->Action = VictoryPose; //SA2 spams the animation 54 every frame, so we force the game to an action which doesn't exist so we can play the animation needed.
		}
		break;
	case Flying:
	case Spinning:
		Miles_DoCollisionAttackStuff(data1);
		break;
	case 66:
		FixAnimationFinalBossOnFrames(co2, data1);
		break;
	case Bounce:
		PlayerResetAngle(data1, co2);
		PlayerGetAccelerationAir(data1, co2, data2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;
	case BounceFloor:
		PlayerResetAngle(data1, co2);
		PlayerGetAccelerationAir(data1, co2, data2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;
	case Grinding:
		DoGrindThing(data1, data2, co2, co2Miles);
		PlayGrindAnimation(data1, co2); //not called by the game, custom function to play animation for Tails
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Miles, data2);
		break;
	case HandGrinding: //Or whatever you call that thing in CG
		SomethingAboutHandGrind(data1, data2, co2Miles);
		MoveCharacterOnRail(data1, co2, data2);
		SomethingAboutHandGrind2(data1, data2, co2Miles);
		break;
	case Action_Board:
	{
		PhysicsBoardStuff(co2, data1, data2, 7.8200002);
		PlayerGetSpeed(data1, co2, data2);
		int checkPos = PlayerSetPosition(data1, data2, co2);
		if (checkPos != 2)
		{
			PlayerResetPosition(data1, data2, co2);
			BoardSparklesMaybe(data2, data1, co2Miles);
		}
	}
		break;
	case 79:
	case 80:
		PlayerResetAngle(data1, co2);
		PhysicsBoardStuff2(data1, data2, co2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;
	case Rolling:
		RollPhysicControlMain(data1, data2, co2);
		Miles_DoCollisionAttackStuff(data1);
		Miles_UnrollCheckInput(data1, co2);
		break;
	case LightDash:
	{
		CheckRefreshLightDashTimer(co2, data1);
		Sonic_InitLightDash(data1, co2, data2, co2Miles);
		int check = PlayerSetPosition(data1, data2, co2);
		if (check == 2) {
			if (((short)CurrentLevel != LevelIDs_GreenHill)) {
				PlaySoundProbably(0x7f, 0, 0, 0);
			}

			data1->Action = 16;
			co2->AnimInfo.Next = 24;
			data1->Status = data1->Status & 0xfbff;

			//PlaySound3(24, 0x2012);
			CrashStar_Load();
			CheckAndDisplayAfterImage(data1, co2, co2Miles);
			//PlayerAfterImageThing(sonicCo2, sonicCo2);
		}
		else {
			if (check == 0)
			{
				CheckAndDisplayAfterImage(data1, co2, co2Miles);
				PlayerResetPosition(data1, data2, co2);
			}
			else {
				data1->Action = 10;
				co2->AnimInfo.Next = 15;
				data1->Status &= 0xFBFFu;
				if (njScalor(&data2->spd) <= 2.0) {
					if (&data2->spd)
					{
						data2->spd.z = 0.0;
						data2->spd.y = 0.0;
						data2->spd.x = 0.0;
					}
				}
				else {
					njUnitVector(&data2->spd);
					data2->spd.x = data2->spd.x * 2.0;
					data2->spd.y = data2->spd.y * 2.0;
					data2->spd.z = data2->spd.z * 2.0;
				}
				PlayerResetPosition(data1, data2, co2);

				if (njScalor(&co2->Speed) <= 2.0) {
					co2->Speed.x = 0.0;
					co2->Speed.y = 0.0;
					co2->Speed.z = 0.0;
					CheckAndDisplayAfterImage(data1, co2, co2Miles);
					//PlayerAfterImageThing(sonicCo2, sonicCo2);
				}
				else {
					njUnitVector(&co2->Speed);
					co2->Speed.x = co2->Speed.x * 2.0;
					co2->Speed.y = co2->Speed.y * 2.0;
					co2->Speed.z = 2.0 * co2->Speed.z;
				}
			}
		}
	}
	break;
	case FloatingOnWater:
		Miles_GetFloat(data1, co2);
		PlayerResetAngle(data1, co2);
		PlayerGetRotation(data1, data2, co2);
		PlayerGetAccelerationAir(data1, co2, data2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);

		if (co2->PhysData.CameraY + data1->Position.y > co2->idk5)
		{
			co2->AnimInfo.Next = FloatingWaterAnim;
		}

		break;
	case Swimming:
		Miles_GetFloat(data1, co2);
		PlayerResetAngle(data1, co2);
		PlayerGetAccelerationAir(data1, co2, data2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;
	case Diving:
		PlayerResetAngle(data1, co2);
		PlayerGetAccelerationAir(data1, co2, data2);
		PlayerGetSpeed(data1, co2, data2);
		PlayerSetPosition(data1, data2, co2);
		PlayerResetPosition(data1, data2, co2);
		break;
	case VictoryPose:
		if (isSuperForm())
			co2->AnimInfo.Current = VictorySuperForm;
		else
			co2->AnimInfo.Current = VictoryAnim;
		AnimateMilesTails(data1, co2, co2Miles);
		break;
	}

	MilesFly(data1, co2);
}

signed char GetCharacterLevel() {
	for (int i = 0; i < 33; i++)
	{
		if (CurrentLevel == StageSelectLevels[i].Level)
		{
			return StageSelectLevels[i].Character;
		}
	}

	return -1;
}

int BannedMilesLevel[10] = { LevelIDs_SonicVsShadow1, LevelIDs_Route101280, LevelIDs_KartRace, LevelIDs_TailsVsEggman1, LevelIDs_TailsVsEggman2,  LevelIDs_SonicVsShadow2, LevelIDs_KnucklesVsRouge,
LevelIDs_BigFoot, LevelIDs_FlyingDog, LevelIDs_HotShot
};

bool isLevelBanned() {
	for (int i = 0; i < LengthOfArray(BannedMilesLevel); i++)
	{
		if (CurrentLevel == BannedMilesLevel[i])
			return true;
	}

	return false;
}

void LoadCharacter_r() {
	if (!TwoPlayerMode && !isLevelBanned()) {
		if (isMilesAdventure || isMechRemoved && GetCharacterLevel() == Characters_MechTails)
			CurrentCharacter = Characters_Tails;
	}

	auto original = reinterpret_cast<decltype(LoadCharacter_r)*>(LoadCharacters_t->Target());
	original();

	CheckAndSetHackObjectMiles();

	for (int i = 0; i < 2; i++) {
		if (isCharaSelect() && MainCharObj2[i]->CharID == Characters_Tails)
		{
			MainCharObj2[i]->AnimInfo.Animations = TailsAnimationList_R; //Overwrite Tails list animation to fix chara select plus crash.
		}
	}

	return;
}

void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);
	Miles_CheckNextActions_t = new Trampoline(0x751CB0, 0x751CB5, Miles_CheckNextActionsASM);
	Tails_RunsAction_t = new Trampoline((int)Tails_runsAction, (int)Tails_runsAction + 0x7, Tails_runsAction_r);

	if (isMilesAdventure || isMechRemoved) {
		init_RankScore();
	}

	LoadCharacters_t = new Trampoline((int)LoadCharacters, (int)LoadCharacters + 0x6, LoadCharacter_r);

	//Improve physic
	if (isCustomPhysics) {
		PhysicsArray[Characters_Tails].AirAccel = 0.050;
		PhysicsArray[Characters_Tails].Brake = -0.25;
		PhysicsArray[Characters_Tails].HangTime = 60;
		PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
		PhysicsArray[Characters_Tails].GroundAccel = 0.1618;
		PhysicsArray[Characters_Tails].RollDecel = -0.008;
		PhysicsArray[Characters_Tails].Run1 = 2.8;
		PhysicsArray[Characters_Tails].Run2 = 5.09;
	}

	Init_MilesActions();
	Init_MilesFly();

	//Custom anim + new moves
	Init_NewAnimation();

	Init_MilesSpin();

	if (isCustomAnim) {
		WriteJump(reinterpret_cast<void*>(0x7512ea), CheckAnimateTailsAction);
	}

	Init_StartEndPos();
	Init_VoicesFixes();

	//Draw the tails depending on the action
	WriteCall((void*)0x750B32, Miles_DrawTail);
	WriteCall((void*)0x750BB8, Miles_DrawTail);

	WriteData((int**)0x7952fa, ShadowActionWindowTextIndexes);
}