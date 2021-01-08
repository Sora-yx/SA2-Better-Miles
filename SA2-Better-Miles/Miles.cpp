#include "stdafx.h"
#include <fstream>
#include <iostream>

Trampoline* Tails_Main_t = nullptr;
AnimationIndex newTailsAnimIndex[118 + 2];

/*static const void* const GetAnalogPtr2 = (void*)0x45A870;

signed int __declspec() GetAnalog(EntityData1* a1, CharObj2Base* a2, signed int* a3, int a4)
{
	__asm
	{
		push[esp + 0Ch] // a4
		push[esp + 0Ch] // int *a3
		push[esp + 0Ch] // a2
		push eax // a1

		// Call your __cdecl function here:
		call GetAnalogPtr2

		add esp, 4 // a1<eax> is also used for return value
		add esp, 4 // a2
		add esp, 4 // int *a3
		add esp, 4 // a4
		retn
	}
}*/



void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2_* data2 = EntityData2Ptrs[0];

	switch (data1->Action)
	{
	case stand:
	case 1:
	case 2:
		if (co2->Speed.x < 2)
			Miles_CheckSpinAttack(data1, co2);
		break;
	case victory: //SA2 spams the animation 54 every frame, so we force the game to an action which doesn't exist so we can play the animation needed.
		co2->field_28 = VictoryAnim;
		co2->AnimInfo.Next = VictoryAnim;
		data1->Action = RealVictory;
		break;
	case RealVictory:
		co2->AnimInfo.Current = VictoryAnim;
		break;
	}

	MilesFly(data1, co2, data2);
}

void LoadCharacterAndNewAnimation() {

	CurrentCharacter = Characters_Tails;
	LoadCharacters();

	if (MainCharObj2[0]->CharID != Characters_Tails)
		return;

	MainCharObj2[0]->AnimInfo.Animations = TailsAnimationList_R;
}


void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);

	//Miles_SpinInit();

	//Improve physic
	PhysicsArray[Characters_Tails].AirAccel = 0.050;
	PhysicsArray[Characters_Tails].Brake = -0.25;
	PhysicsArray[Characters_Tails].HangTime = 60;
	PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
	PhysicsArray[Characters_Tails].GroundAccel = 0.14;

	MilesFly_Init();

	WriteCall((void*)0x439b13, LoadCharacterAndNewAnimation);	
	WriteCall((void*)0x43cada, LoadCharacterAndNewAnimation);

	voices_Init();
}