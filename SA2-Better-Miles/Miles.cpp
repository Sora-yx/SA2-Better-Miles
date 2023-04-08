#include "pch.h"
#include "patches.h"

TaskHook Tails_Main_t(Tails_Main);
TaskHook Tails_Delete_t(Tails_Delete);
UsercallFunc(signed int, Miles_CheckNextActions_t, (EntityData2* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4),
	(a1, a2, a3, a4), 0x751CB0, rEAX, rECX, rEBX, rEDI, rESI);
static FunctionHook<void, EntityData1*, EntityData2*, CharObj2Base*, TailsCharObj2*> Tails_RunsAction_t(Tails_RunActions);
Trampoline* LoadCharacters_t = nullptr;
static FunctionHook<void, int> LoadMechTails_t(LoadMechTails);
static Trampoline* Init_LandColMemory_t = nullptr;

UsercallFunc(signed int, Tails_CheckActionWindow_t, (taskwk* data1, motionwk2* data2, playerwk* co2, TailsCharObj2* sonicCO2), (data1, data2, co2, sonicCO2), 0x752400, rEAX, rEAX, rEDX, rECX, stack4);

static Sint32 Tails_CheckActionWindow_r(taskwk* twp, motionwk2* mwp, playerwk* pwp, TailsCharObj2* co2M)
{
	// This code is based on the pseudocode of the original function
	int  pnum = pwp->PlayerNum;
	char action = pwp->field_D[0];
	int  count = pwp->ActionWindowItemCount;
	int  i = 0;

	if (count)
	{
		if (count > 0)
		{
			do
			{
				if (pwp->field_D[0] == pwp->ActionWindowItems[i])
				{
					break;
				}
				++i;
			} while (i < count);
			action = pwp->field_D[0];
		}

		if (count == i)
		{
			action = pwp->ActionWindowItems[0];
		}

		if (action == LightDash)
		{
			pwp->field_D[1] = action;

			if ((Controllers[pnum].press & LightDashBtn) == 0)
			{
				return FALSE;
			}

			Miles_PerformLightDash((CharObj2Base*)pwp, (EntityData1*)twp);
			return TRUE;
		}
	}

	return Tails_CheckActionWindow_t.Original(twp, mwp, pwp, co2M);
}


signed int __cdecl Miles_CheckNextAction_r(EntityData2* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4)
{

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
		if (!isRando()) {

			if (setGrindingNextAction(a2, a3, a4))
				return 1;
			else
				return 0;
		}
		break;
	case 32:

		if (!isRando()) {

			AnimationIndex* sa2anim = getCharAnim_r();

			if (sa2anim)
			{
				if (!sa2anim[200].Animation) {
					return 1;
				}
			}
			else {

				if (!CharacterAnimations[200].Animation) {
					return 1;
				}
			}
			if (SetHandGranding(a1, a3, a4)) {
				return 1;
			}
			else {
				return 0;
			}
		}
		break;
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
		MainCharObj1[a3->PlayerNum]->field_2 = 1;
		a4->NextAction = 0;
		return 0;
	}

	return Miles_CheckNextActions_t.Original(a1, a2, a3, a4);
}


void __cdecl Tails_runsAction_r(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, TailsCharObj2* co2Miles)
{
	auto pwp = (playerwk*)co2;
	auto twp = (taskwk*)data1;
	auto mwp = (motionwk2*)data2;

	if (!data1 || !co2)
		return;

	Check_LightDash(twp, pwp);


	if (data1->Action == Spinning)
	{

	}
	else if (data1->Action == SpinningAir)
	{

	}


	Tails_RunsAction_t.Original(data1, data2, co2, co2Miles);

	CheckAndFixTailsRotation(co2, co2Miles);

	switch (data1->Action)
	{
	case Standing:
	case Running:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		if (co2->Speed.x < 1.3f || SpinBtn != RollBtn)
		{
			Miles_CheckSpinAttack(co2Miles, data1, co2, data2);
		}

		if (co2->Speed.x > 1.3f)
			Miles_RollCheckInput(data1, co2);

		break;
	case Jumping:
		if (Miles_CheckBounceAttack(co2, data1) || Miles_SetNextActionSwim(co2Miles, data1))
			return;

		data1->Status |= Status_Attack;

		Miles_CheckSpinAttack(co2Miles, data1, co2, data2);

		break;
	case 7:
	case 8:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case 10:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		SetNewTailsRotation(co2Miles, -17000);
		Miles_CheckSpinAttack(co2Miles, data1, co2, data2);

		break;
	case 15:
	case 17:
		if (Miles_SetNextActionSwim(co2Miles, data1))
			return;

		break;
	case MysticMelody:
		if (MilesCheckInput(data2, co2Miles, co2, data1)) {
			return;
		}

		if ((co2->AnimInfo.field_C & 1) != 0)
		{
			data1->Action = 0;
		}
		return;
	case Pulley:
		if (!MilesCheckInput(data2, co2Miles, co2, data1)) {
			TailsJump(co2, data1);
		}
		return;
	case Action_AirBubble:
		SetNewTailsRotation(co2Miles, -17000);
		break;
	case Flying:

		Miles_ManageFly(twp, mwp, pwp, co2Miles);

		break;
	case Spinning:
		if (!MilesCheckInput(data2, co2Miles, co2, data1) && !Miles_SetNextActionSwim(co2Miles, data1))
		{
			spinLeaveGroundCheck(twp, pwp, co2Miles);

			if (isCustomAnim)
				spinOnFrames(pwp, data1, co2Miles);
		}
		break;
	case SpinningAir:
		if (!MilesCheckInput(data2, co2Miles, co2, data1) && !Miles_SetNextActionSwim(co2Miles, data1))
		{
			spinLandingCheck(twp, pwp);

			if (isCustomAnim)
				spinOnFrames(pwp, data1, co2Miles);
		}
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
		if (MilesCheckInput(data2, co2Miles, co2, data1))
			return;
		SetNewTailsRotation(co2Miles, -9000);
		CheckGrindThing(data1, data2, co2, co2Miles);
		break;
	case HandGrinding: //Whatever you call that thing in CG
		DoHangGrinding(data1, co2);
		return;
	case 76:
		BoardStuff(data2, co2Miles, data1, co2);
		return;
	case 79:
		if (MilesCheckInput(data2, co2Miles, co2, data1) || (data1->Status & 3) == 0)
		{
			return;
		}

		PlaySoundProbably(8195, 0, 0, 0);
		data1->Action = 76;
		co2->AnimInfo.Next = 121;
		co2->AnimInfo.nframe = 0.0f;
		if (co2->Speed.x <= 0.30000001f)
		{
			co2->Speed.x = 1.0f;
		}
		data1->Rotation.x = data2->Forward.x;
		data1->Rotation.z = data2->Forward.z;
		break;
	case 80:
		BoardJumpStuff(data1, co2Miles, co2, data2);
		break;
	case Action_TurtleDive:

		if (MilesCheckInput(data2, co2Miles, co2, data1))
			return;

		break;
	case Rolling:
		if (MilesCheckInput(data2, co2Miles, co2, data1))
			return;

		Miles_UnrollCheck(data1, data2, co2);
		Miles_UnrollCheckInput(data1, co2);
		return;
	case LightDash:
		CheckLightDashEnd(co2Miles, co2, data1);
		return;
	case FloatingOnWater:
		if (co2->Speed.x > 0.0f)
			SetNewTailsRotation(co2Miles, -17000);

		CheckFloatingStuff(data2, data1, co2, co2Miles);
		break;
	case Swimming:
		SetNewTailsRotation(co2Miles, -17000); //fix "rotation Y" of the tails
		CheckSwimmingStuff(data2, data1, co2, co2Miles);
		break;
	case Diving:
		SetNewTailsRotation(co2Miles, -17000);
		CheckDivingStuff(data2, data1, co2, co2Miles);
		break;
	}


	Tornado_RunsActions(data2, co2Miles, data1, co2);
}

void Tails_Main_r(ObjectMaster* obj)
{
	if (!obj || !obj->Data1.Entity)
		return;

	Tails_Main_t.Original(obj);

	CharObj2Base* co2 = obj->Data2.Character;
	EntityData1* data1 = obj->Data1.Entity;
	EntityData2* data2 = (EntityData2*)obj->EntityData2;
	TailsCharObj2* co2Miles = (TailsCharObj2*)obj->Data2.Undefined;
	char pID = co2->PlayerNum;

	if (data1->Status & Status_Ball)
	{
		spinTimer++;
	}

	switch (data1->Action)
	{
	case Bounce:
		PResetAngle(data1, co2);
		PGetAccelerationAir(data1, co2, data2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);
		break;
	case BounceFloor:
		PResetAngle(data1, co2);
		PGetAccelerationAir(data1, co2, data2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);
		break;
	case Grinding:
		DoGrindThing(data1, data2, co2, co2Miles);
		PlayGrindAnimation(data1, co2); //not called by the game, custom function to play animation for Tails
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Miles, data2);
		break;
	case HandGrinding:
		SomethingAboutHandGrind(data1, data2, co2Miles);
		MoveCharacterOnRail(data1, co2, data2);
		SomethingAboutHandGrind2(data1, data2, co2Miles);
		break;
	case Action_Board:
	{
		PhysicsBoardStuff(co2, data1, data2, 7.8200002f);
		PGetSpeed(data1, co2, data2);
		int checkPos = PSetPosition(data1, data2, co2);
		if (checkPos != 2)
		{
			PResetPosition(data1, data2, co2);
			BoardSparklesMaybe(data2, data1, co2Miles);
		}
		BoardSoundEffect(co2, data1);
	}
	break;
	case 79:
	case 80:
		PResetAngle(data1, co2);
		PhysicsBoardStuff2(data1, data2, co2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);
		break;
	case Rolling:
		RollPhysicControlMain(data1, data2, co2);
		break;
	case LightDash:
	{
		CheckRefreshLightDashTimer(co2, data1);
		Miles_InitLightDash(data1, co2, data2, co2Miles);
		int check = PSetPosition(data1, data2, co2);
		if (check == 2) {
			if (((short)CurrentLevel != LevelIDs_GreenHill)) {
				PlaySoundProbably(0x7f, 0, 0, 0);
			}

			data1->Action = 16;
			co2->AnimInfo.Next = 24;
			data1->Status = data1->Status & 0xfbff;

			//PlaySound3(24, 0x2012);
			CrashStar_Load();
			Miles_DisplayAfterImage(data1, co2, co2Miles);
		}
		else {
			if (check == 0)
			{
				Miles_DisplayAfterImage(data1, co2, co2Miles);
				PResetPosition(data1, data2, co2);
			}
			else {
				data1->Action = 10;
				co2->AnimInfo.Next = 15;
				data1->Status &= 0xFBFFu;
				if (njScalor(&data2->Velocity) <= 2.0f) {
					if (&data2->Velocity)
					{
						data2->Velocity = { 0.0f };
					}
				}
				else {
					njUnitVector(&data2->Velocity);
					data2->Velocity.x *= 2.0f;
					data2->Velocity.y *= 2.0f;
					data2->Velocity.z *= 2.0f;
				}
				PResetPosition(data1, data2, co2);

				if (njScalor(&co2->Speed) <= 2.0f) {
					co2->Speed = { 0.0f };
					Miles_DisplayAfterImage(data1, co2, co2Miles);
				}
				else {
					njUnitVector(&co2->Speed);
					co2->Speed.x += 2.0f;
					co2->Speed.y += 2.0f;
					co2->Speed.z += 2.0f;
				}
			}
		}
	}
	break;
	case FloatingOnWater:
		Miles_GetFloat(data1, co2);
		PResetAngle(data1, co2);
		PGetRotation(data1, data2, co2);
		PGetAccelerationAir(data1, co2, data2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);

		if (co2->PhysData.CameraY + data1->Position.y > co2->SurfaceInfo.TopSurfaceDist)
		{
			co2->AnimInfo.Next = FloatingWaterAnim;
		}
		break;
	case Swimming:
		Miles_GetFloat(data1, co2);
		PResetAngle(data1, co2);
		PGetAccelerationAir(data1, co2, data2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);
		break;
	case Diving:
		PResetAngle(data1, co2);
		PGetAccelerationAir(data1, co2, data2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);
		break;
	case SpinningAir:
	{
		auto RestoreSpeed = co2->PhysData.Weight;
		co2->PhysData.Weight = 0.0199999992f;


		PGetRotation(data1, data2, co2);
		PResetAngle(data1, co2);
		PGetAcceleration(data1, data2, co2);
		PGetSpeed(data1, co2, data2);
		PSetPosition(data1, data2, co2);
		PResetPosition(data1, data2, co2);

		co2->PhysData.Weight = RestoreSpeed;
	}
	break;
	case VictoryPose:

		AnimateMilesTails(data1, co2, co2Miles);
		break;
	}

	Tornado_CallCheckInput(co2, data1);
	Tornado_MainActions(data1, co2, data2);
}

void Tails_Delete_r(ObjectMaster* obj)
{
	Tails_Delete_t.Original(obj);

	Delete_MilesAnim();
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

int BannedMilesLevel[5] = { LevelIDs_FinalHazard, LevelIDs_Route101280, LevelIDs_KartRace, LevelIDs_TailsVsEggman1,
LevelIDs_TailsVsEggman2,
};

bool isLevelBanned() {
	for (int i = 0; i < LengthOfArray(BannedMilesLevel); i++)
	{
		if (CurrentLevel == BannedMilesLevel[i])
			return true;
	}

	return false;
}

extern bool isTornadoTransform;

void RemoveMech(int player)
{

	if (!TwoPlayerMode && CurrentLevel != LevelIDs_Route101280 && CurrentLevel != LevelIDs_KartRace
		&& CurrentLevel != LevelIDs_TailsVsEggman1 && CurrentLevel != LevelIDs_TailsVsEggman2)
	{
		if (!isTornadoTransform)
		{
			CurrentCharacter = Characters_Tails;
			LoadTails(player);
			return;
		}
	}

	LoadMechTails_t.Original(player);
}

void LoadTailsExtra(char pnum)
{
	auto p = MainCharObj2[pnum];
	Load_MilesNewAnim();
	SetSpacePhysics(p);
	Miles_LoadJmpBall((TailsCharObj2*)MainCharacter[pnum]->Data2.Undefined);
	spinTimer = 0;
	CheckAndSetHackObject(p);
}

//used to load object hack
void InitLandColMemory_r()
{
	bool isMiles = false;
	resetMechWKPtr();

	for (uint8_t i = 0u; i < 2u; i++) 
	{

		auto p = MainCharObj2[i];
		if (p)
		{
			if (p->CharID == Characters_Tails)
			{
				LoadTailsExtra(i);
				isMiles = true;
			}

			if (p->CharID == Characters_Tails || p->CharID == Characters_MechTails)
			{
				LoadTornado_ModelAnim();
				break;
			}
		}
	}


	if (!isMiles)
	{
		MilesCO2Extern = nullptr; //reset the pointer because the vanilla game never do lol
	}

	VoidFunc(origin, Init_LandColMemory_t->Target());
	origin();
}


void LoadCharacter_r() {

	if (!TwoPlayerMode && !isLevelBanned()) {

		if (isMilesAdventure || isMechRemoved && (GetCharacterLevel() == Characters_MechTails && CurrentCharacter == Characters_MechTails))
		{
			CurrentCharacter = Characters_Tails;
		}

	}

	if (CurrentLevel == LevelIDs_ChaoWorld)
	{
		char curChar = CurrentCharacter;

		if (curChar == Characters_MechEggman || curChar == Characters_MechTails)
		{
			if (MainCharacter[0])
				DeleteObject_((ObjectMaster*)MainCharacter[0]);

			if (isFirstStageLoad != 1 || negative_2 == -2)
			{
				if (CurrentCharacter == Characters_MechEggman)
					CurrentCharacter = Characters_Eggman;
				else
					CurrentCharacter = Characters_Tails;
			}
		}
	}

	auto original = reinterpret_cast<decltype(LoadCharacter_r)*>(LoadCharacters_t->Target());
	original();
}

void BetterMiles_Init() {

	Tails_Main_t.Hook(Tails_Main_r);
	Miles_CheckNextActions_t.Hook(Miles_CheckNextAction_r);
	Tails_RunsAction_t.Hook(Tails_runsAction_r);
	Tails_CheckActionWindow_t.Hook(Tails_CheckActionWindow_r);
	Tails_Delete_t.Hook(Tails_Delete_r);
	LoadCharacters_t = new Trampoline((int)LoadCharacters, (int)LoadCharacters + 0x6, LoadCharacter_r);

	Init_LandColMemory_t = new Trampoline((int)0x47BB50, (int)0x47BB57, InitLandColMemory_r);

	if (isMechRemoved)
	{
		LoadMechTails_t.Hook(RemoveMech);
	}

	if (isMilesAdventure || isMechRemoved)
	{
		init_RankScore();
	}


	//Improve physic
	if (isCustomPhysics)
	{
		//copy Sonic physics since it's more closer to sadx tails
		PhysicsArray[Characters_Tails] = PhysicsArray[Characters_Sonic];

		//adjust to sadx Tails physics
		PhysicsArray[Characters_Tails].FloorGrip = 1.5f;
		PhysicsArray[Characters_Tails].JogSpeed = 0.49f;
		PhysicsArray[Characters_Tails].RunSpeed = 2.2f;
		PhysicsArray[Characters_Tails].RunAccel = 0.06f;
		PhysicsArray[Characters_Tails].Radius = 3.5f;
		PhysicsArray[Characters_Tails].Height = 9.0f;
		PhysicsArray[Characters_Tails].CameraY = 6.0f;
		PhysicsArray[Characters_Tails].CenterHeight = 4.5f;
	}


	Init_ObjectsHacks();
	Init_MilesFly();
	Init_TailsMechHack();

	//Custom anim + new moves
	Init_NewAnimation();

	Init_MilesSpin();

	Init_JumpBallhack();

	Init_StartEndPos();
	Init_VoicesFixes();
	init_Patches();

}