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


//Jump to a specific address where the game will call the function to animate Miles's tails
static const void* const loc_74D34C = (void*)0x74D34C;
__declspec(naked) void GoToAnimatedTailAnimation()
{
	__asm jmp loc_74D34C
}


//Rework the condition to add the victory pose
static const void* const loc_7512F2 = (void*)0x7512F2;
__declspec(naked) void  CheckVictoryPose() {


	if (MainCharObj1[0]->Action != 24 || MainCharObj1[0]->Action != VictoryPose || MainCharObj1[0]->Action != ObjectControl || MainCharObj1[0]->Action != Pulley)
	{
		_asm jmp loc_7512F2
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


signed int Tails_Jump(CharObj2Base* co2, EntityData1* data) //Used for pulley
{

	if ((data->Status & 0x4000) != 0 || !Jump_Pressed[co2->PlayerNum])
	{
		return 0;
	}

	data->Action = Jumping;
	co2->Speed.y = co2->PhysData.JumpSpeed;
	co2->AnimInfo.Next = 65;
	data->Status &= 65533u;
	data->Status &= 0xFFFDu;
	(co2->field_12) = 0;
	PlaySoundProbably(0x2000, 0, 0, 0);
	PlayVoice(2, 1627);
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
	NJS_VECTOR result;
	NJS_VECTOR result2;


	switch (data1->Action)
	{
	case Standing:
	case Running:
		if (!isCustomAnim || CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7)
			return;

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
			co2->field_28 = VictoryAnim;
			co2->AnimInfo.Next = VictoryAnim;
			data1->Action = VictoryPose; //SA2 spams the animation 54 every frame, so we force the game to an action which doesn't exist so we can play the animation needed.
		}
		break;
	case Pulley:
		Tails_Jump(co2, data1);
		break;
	case Spinning:
		if (isCustomAnim)
			spinOnFrames(co2, data1);
		break;
	case 71:
		DoGrindThing(data1, data2, co2, co2Miles);
		MoveCharacterOnRail(data1, co2, data2);
		LoadRailParticules(co2Miles, data2);
		CheckGrindThing(data1, data2, co2, co2Miles);
		//GoToAnimatedTailAnimation();
	break;
	case VictoryPose:
		co2->AnimInfo.Current = VictoryAnim;
		GoToAnimatedTailAnimation();
		break;
	case Rolling:
		Miles_DoCollisionAttackStuff(data1);
		Miles_UnrollCheckInput(data1, co2);
		break;
	}

	MilesFly(data1, co2, data2);
}

void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);
	Miles_CheckNextActions_t = new Trampoline(0x751CB0, 0x751CB5, Miles_CheckNextActionsASM);

	//Improve physic
	PhysicsArray[Characters_Tails].AirAccel = 0.050;
	PhysicsArray[Characters_Tails].Brake = -0.25;
	PhysicsArray[Characters_Tails].HangTime = 60;
	PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
	PhysicsArray[Characters_Tails].GroundAccel = 0.14;

	Init_MilesActions();
	MilesFly_Init();

	//WriteData<5>((int*)0x751c6e, 0x90);	
	//WriteData<4>((int*)0x74e175, 0x90);

	//Custom anim + new moves
	Init_NewAnimation();

	if (isCustomAnim) {
		Miles_SpinInit();
		WriteJump(reinterpret_cast<void*>(0x7512ea), CheckVictoryPose);
	}


	//WriteJump(reinterpret_cast<void*>(0x751c67), AddStatueAttack);

	WriteData<1>((int*)0x472C99, 0x17); //remove miles check shit

	//Audio fix
	voices_Init();
}