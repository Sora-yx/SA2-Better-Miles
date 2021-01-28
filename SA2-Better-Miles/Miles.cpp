#include "stdafx.h"
#include <fstream>
#include <iostream>

Trampoline* Tails_Main_t = nullptr;
Trampoline* Miles_CheckNextActions_t = nullptr;


//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.
static const void* const Miles_CheckNextActionPtr = (void*)0x751CB0;
signed int Miles_CheckNextActions_original(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

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


signed int __cdecl Miles_CheckNextActions_r(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

	switch (a4->NextAction)
	{
	 case 20: //Pulley
	 	a4->Status &= 0xDAFFu;
	 	a3->Speed = { 0, 0, 0 };
	 	a4->Action = Pulley;
	 	a3->AnimInfo.Next = 75;
	 	return 1;
	 case 31:
		setGrindingNextAction(a1, a2, a3, a4);
	 	return 1;
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
	 case 38:
		 a4->Action = 6;
		 return 1;
	 case 39:
		 a4->Action = Spinning;
		 a3->AnimInfo.field_8 = 0;
		 a3->AnimInfo.Current = Spin1;
		 Play3DSound_Pos(8200, &a4->Position, 0, 0, 0);
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



int ActionArray[6] = { Jumping, 24, ObjectControl, Pulley, 66, VictoryPose };

//Edit the function which checks where it needs to animate Miles's tails to add more actions.
static const void* const loc_7512F2 = (void*)0x7512F2; 
__declspec(naked) void  CheckVictoryPose() {


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


signed int Tails_Jump(CharObj2Base* co2, EntityData1* data)
{

	short curStat = data->Status;
	char curPlay = co2->PlayerNum;

	if ((curStat & 0x4000) != 0 || !Jump_Pressed[curPlay])
	{
		return 0;
	}

	data->Action = Action_Jump;
	data->NextAction = Action_Jump;
	data->Status = 0;
	co2->AnimInfo.Next = 65;
	co2->Speed.y = co2->PhysData.JumpSpeed;
	return 1;
}


void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2_* data2 = EntityData2Ptrs[0];
	TailsCharObj2* co2Miles = (TailsCharObj2*)MainCharObj2[0];
	

	switch (data1->Action)
	{
	case Standing:
	case Running:
		if (co2->Speed.x < 1.3) {
			Miles_CheckSpinAttack(data1, co2);
		}
		else {
			//Miles_RollCheckInput(data1, co2);
		}
		break;
	case Jumping:
		Miles_DoCollisionAttackStuff(data1);
		break;
	case ObjectControl:
		if (!isCustomAnim)
			return;

		if (TimerStopped != 0) { //Check if the level is finished
			if (isSuperForm()) {
				co2->field_28 = VictorySuperForm;
				co2->AnimInfo.Next = VictorySuperForm;
			}
			else {
				co2->field_28 = VictoryAnim;
				co2->AnimInfo.Next = VictoryAnim;
			}
			data1->Action = VictoryPose; //SA2 spams the animation 54 every frame, so we force the game to an action which doesn't exist so we can play the animation needed.
		}
		break;
	case Pulley:
		Tails_Jump(co2, data1);
		break;
	case Flying:
		if (isSuperForm() && co2->AnimInfo.Next == 92 || co2->AnimInfo.Current == 92)
		{
			co2->AnimInfo.Next = 15;
		}
		break;
	case Spinning:
		if (isCustomAnim)
			spinOnFrames(co2, data1);
		break;
	case 66:
		FixAnimationFinalBossOnFrames(co2, data1);
		AnimateMilesTails(data1, co2, co2Miles);
		break;
	case Grinding:
		DoGrindThing(data1, data2, co2, co2Miles);
		PlayGrindAnimation(data1, co2);
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Miles, data2);
		CheckGrindThing(data1, data2, co2, co2Miles);
		break;
	case HandGrinding: //Or whatever you call that thing in CG
		MoveCharacterOnRail(data1, co2, data2);
		SomethingAboutHandGrind(data1, data2, co2Miles);
		SomethingAboutHandGrind2(data1, data2, co2Miles);
		DoHangGrinding(data1, co2);
		break;
	case 73:
		CheckTrick(data1, co2, data2, co2Miles);
		break;
	case VictoryPose:
		if (isSuperForm())
			co2->AnimInfo.Current = VictorySuperForm;
		else
			co2->AnimInfo.Current = VictoryAnim;
		AnimateMilesTails(data1, co2, co2Miles);
		break;
	case Rolling:
		Miles_DoCollisionAttackStuff(data1);
		Miles_UnrollCheckInput(data1, co2);
		break;
	}


	MilesFly(data1, co2, data2);
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


void LoadCharacter_r() {

	PDS_PERIPHERAL p1 = Controllers[0];

	if (!TwoPlayerMode && CurrentLevel != LevelIDs_FinalHazard && CurrentLevel != LevelIDs_Route101280 && CurrentLevel != LevelIDs_KartRace) {

		if (isMilesAdventure || isMechRemoved && GetCharacterLevel() == Characters_MechTails)
			CurrentCharacter = Characters_Tails;
	}

	LoadCharacters();
}



void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);
	Miles_CheckNextActions_t = new Trampoline(0x751CB0, 0x751CB5, Miles_CheckNextActionsASM);

	if (isMilesAdventure || isMechRemoved) {
		WriteCall((void*)0x439b13, LoadCharacter_r);
		WriteCall((void*)0x43cada, LoadCharacter_r);
		init_RankScore();
	}

	//Improve physic
	PhysicsArray[Characters_Tails].AirAccel = 0.050;
	PhysicsArray[Characters_Tails].Brake = -0.25;
	PhysicsArray[Characters_Tails].HangTime = 60;
	PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
	PhysicsArray[Characters_Tails].GroundAccel = 0.14;

	Init_MilesActions();
	Init_MilesFly();

	//Custom anim + new moves
	Init_NewAnimation();

	if (isCustomAnim) {
		Init_MilesSpin();
		WriteJump(reinterpret_cast<void*>(0x7512ea), CheckVictoryPose);
	}

	Init_StartEndPos();
	Init_VoicesFixes();
}