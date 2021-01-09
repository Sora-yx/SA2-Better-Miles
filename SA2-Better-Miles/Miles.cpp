#include "stdafx.h"
#include <fstream>
#include <iostream>

Trampoline* Tails_Main_t = nullptr;
AnimationIndex newTailsAnimIndex[130];

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


static const void* const sub_460860Ptr = (void*)0x460860;
static void __declspec(naked) PGetAccelerationASM(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3)
{
	__asm
	{
		push[esp + 04h] // a3
		push ebx // a2
		push eax // a1

		// Call your __cdecl function here:
		call sub_460860Ptr

		pop eax // a1
		pop ebx // a2
		add esp, 4 // a3
		retn
	}
}


static const void* const sub_4616E0Ptr = (void*)0x4616E0;
void __declspec() sub_4616E0ASM(EntityData1* a1, EntityData2_* a2, CharObj2Base* a3)
{
	__asm
	{
		push[esp + 08h] // a3
		push[esp + 08h] // a2
		push eax // a1

		// Call your __cdecl function here:
		call sub_4616E0Ptr

		pop eax // a1
		add esp, 4 // a2
		add esp, 4 // a3
		retn
	}
}

static const void* const sub_469050Ptr = (void*)0x469050;
static void __declspec(naked) sub_469050ASM(EntityData1* a1, EntityData2_* a2, CharObj2Base* a3)
{
	__asm
	{
		push[esp + 04h] // a3
		push ebx // a2
		push eax // a1

		// Call your __cdecl function here:
		call sub_469050Ptr

		pop eax // a1
		pop ebx // a2
		add esp, 4 // a3
		retn
	}
}




AnimationInfo TailsAnimationList_R[] = {
	{ 95, 208, 3, 0, 0.0625f, 0.1f },
	{ 95, 208, 3, 1, 0.25f, 0.1f },
	{ 95, 208, 3, 2, 0.25f, 0.1f },
	{ 95, 208, 4, 0, 0.25f, 0.1f },
	{ 4, 208, 3, 4, 0.03125f, 0.1f },
	{ 5, 208, 3, 5, 0.03125f, 0.1f },
	{ 96, 208, 11, 6, 0.25f, 3.4f },
	{ 113, 208, 11, 7, 0.25f, 1.4f },
	{ 114, 208, 11, 8, 0.25f, 1 },
	{ 97, 208, 11, 9, 0.25f, 1 },
	{ 97, 208, 10, 10, 0.25f, 1 },
	{ 11, 208, 11, 11, 0.25f, 0.4f },
	{ 12, 208, 10, 12, 0.25f, 0.7f },
	{ 13, 208, 3, 13, 0.25f, 0.4f },
	{ 14, 208, 4, 15, 0.125f, 0.3f },
	{ 15, 208, 3, 15, 0.25f, 0.4f },
	{ 115, 208, 4, 0, 1, 0.2f },
	{ 17, 208, 4, 0, 1, 0.4f },
	{ 18, 208, 9, 0, 0.25f, 0.3f },
	{ 19, 208, 4, 20, 0.125f, 0.2f },
	{ 20, 208, 3, 20, 0.25f, 0.6f },
	{ 21, 208, 6, 21, 1, 0.1f },
	{ 22, 208, 4, 1, 1, 1 },
	{ 23, 208, 3, 23, 0.0625f, 1 },
	{ 24, 208, 4, 25, 0.25f, 0.4f },
	{ 25, 208, 4, 0, 0.0625f, 0.3f },
	{ 26, 208, 4, 0, 0.0625f, 1 },
	{ 27, 208, 4, 0, 1, 1 },
	{ 28, 208, 3, 28, 0.0625f, 0.2f },
	{ 29, 208, 3, 29, 0.0625f, 0.2f },
	{ 30, 208, 3, 30, 0.5f, 1 },
	{ 99, 208, 4, 35, 0.5f, 0.3f },
	{ 117, 208, 11, 32, 0.5f, 1 },
	{ 33, 208, 4, 35, 0.5f, 1 },
	{ 34, 208, 4, 35, 0.5f, 1 },
	{ 100, 208, 3, 35, 0.5f, 0 },
	{ 36, 208, 3, 36, 0.03125f, 0 },
	{ 37, 208, 3, 37, 0.03125f, 0 },
	{ 116, 208, 11, 38, 0.5f, 1 },
	{ 39, 208, 4, 6, 0.5f, 0.5f },
	{ 40, 208, 3, 40, 0.5f, 0.6f },
	{ 41, 208, 3, 41, 0.5f, 0.4f },
	{ 103, 208, 3, 42, 0.5f, 0.3f },
	{ 43, 208, 4, 44, 0.5f, 0.2f },
	{ 44, 208, 3, 44, 0.5f, 0.1f },
	{ 45, 208, 3, 45, 0.5f, 0.1f },
	{ 46, 208, 4, 47, 0.5f, 0.1f },
	{ 47, 208, 3, 47, 0.5f, 0.3f },
	{ 112, 208, 4, 35, 0.5f, 0.2f },
	{ 49, 208, 4, 0, 0.5f, 0.3f },
	{ 50, 208, 4, 0, 0.5f, 0.3f },
	{ 51, 208, 4, 15, 0.5f, 0.3f },
	{ 52, 208, 4, 15, 0.5f, 0.3f },
	{ 99, 208, 7, 0, 1, 0.3f },
	{ 98, 208, 6, 54, 0.5f, 1 },
	{ 55, 208, 3, 55, 0.125f, 0.3f },
	{ 56, 208, 4, 15, 1, 0.25f },
	{ 57, 208, 4, 58, 0.125f, 0.1f },
	{ 58, 208, 3, 58, 1, 0.1f },
	{ 59, 208, 6, 59, 1, 0.2f },
	{ 60, 208, 6, 60, 0.25f, 1 },
	{ 61, 208, 4, 0, 0.25f, 4 },
	{ 109, 208, 6, 62, 0.25f, 0.1f },
	{ 110, 208, 4, 0, 0.25f, 0.3f },
	{ 111, 208, 4, 0, 0.25f, 0.3f },
	{ 105, 208, 4, 66, 0.25f, 0.4f },
	{ 106, 208, 3, 66, 0.25f, 0.1f },
	{ 107, 208, 4, 68, 0.125f, 0.4f },
	{ 108, 208, 3, 68, 0.125f, 0.4f },
	{ 69, 208, 4, 70, 0.25f, 0.1f },
	{ 70, 208, 3, 70, 1, 0.2f },
	{ 71, 208, 9, 0, 0.125f, 0.2f },
	{ 72, 208, 6, 72, 0.25f, 0.2f },
	{ 73, 208, 4, 0, 0.25f, 0.3f },
	{ 74, 208, 3, 74, 0.25f, 0.4f },
	{ 75, 208, 3, 75, 0.25f, 0.1f },
	{ 76, 208, 6, 76, 0.25f, 0.3f },
	{ 77, 208, 3, 77, 0.25f, 0.8f },
	{ 104, 208, 3, 78, 0.125f, 0.2f },
	{ 79, 208, 4, 0, 0.25f, 0.3f },
	{ 80, 208, 5, 81, 0.25f, 0.5f },
	{ 81, 208, 4, 0, 0.25f, 0.5f },
	{ 82, 208, 9, 0, 0.25f, 0.5f },
	{ 83, 208, 4, 0, 0.0625f, 0.15f },
	{ 84, 208, 4, 0, 0.0625f, 0.15f },
	{ 85, 208, 6, 85, 0.25f, 0.1f },
	{ 86, 208, 3, 86, 1, 0.5f },
	{ 87, 208, 3, 87, 0.03125f, 0.1f },
	{ 88, 208, 3, 88, 0.03125f, 0.1f },
	{ 89, 208, 7, 0, 0.25f, 0.25f },
	{ 90, 208, 3, 90, 0.0625f, 0.1f },
	{ 91, 208, 4, 92, 0.25f, 0.1f },
	{ 92, 208, 3, 92, 0.25f, 0.1f },
	{ 93, 208, 6, 93, 0.25f, 0.1f },
	{ 94, 208, 4, 0, 0.125f, 1 },
	{ 95, 208, 3, 95, 0.0625f, 0.1f },
	{ 96, 208, 11, 96, 0.25f, 3.4f },
	{ 97, 208, 10, 97, 0.25f, 1 },
	{ 98, 208, 6, 98, 0.5f, 1 },
	{ 99, 208, 4, 100, 0.5f, 1 },
	{ 100, 208, 3, 100, 0.5f, 0 },
	{ 101, 208, 4, 70, 0.25f, 0.1f },
	{ 102, 208, 8, 102, 1, 0.1f },
	{ 103, 208, 3, 103, 0.5f, 0.5f },
	{ 104, 208, 3, 104, 0.125f, 0.2f },
	{ 105, 208, 4, 66, 0.25f, 0.4f },
	{ 106, 208, 3, 66, 0.25f, 0.4f },
	{ 107, 208, 4, 68, 0.125f, 0.4f },
	{ 108, 208, 3, 68, 0.125f, 0.4f },
	{ 109, 208, 6, 109, 0.25f, 0.1f },
	{ 110, 208, 4, 0, 0.25f, 0.3f },
	{ 111, 208, 4, 0, 0.25f, 0.3f },
	{ 112, 208, 4, 0, 1, 0.3f },
	{ 113, 208, 11, 0, 0.25f, 0.3f },
	{ 114, 208, 11, 0, 0.25f, 0.3f },
	{ 115, 208, 4, 0, 1, 0.3f },
	{ 116, 208, 11, 0, 0.25f, 0.3f },
	{ 117, 208, 11, 0, 0.25f, 0.3f },
	{ VictoryAnim, 208, 6, 119, 0.5f, 0.7F },
	{ VictoryPoseEnd, 208, 6, 0, 0.5f, 1.0F },
	{ Spin1, 208, 6, 0, 0.125f, 0.7F },
	{ Spin2, 208, 6, 0, 0.125f, 0.7F },
	{ Spin3, 208, 6, 0, 0.125f, 0.7F },
	{ Spin4, 208, 6, 0, 0.125f, 0.7F },
	{ Spin5, 208, 6, 0, 0.125f, 0.7F },
	{ Spin6, 208, 6, 0, 0.125f, 0.7F },
	{ Spin7, 208, 6, 0, 0.125f, 0.7F },
	{ Spin8, 208, 6, 0, 0.125f, 0.7F },
	{ Spin9, 208, 6, 0, 0.125f, 0.7F },
	{ Spin10, 208, 6, 0, 0.125f, 1.0F },
};



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
	case Spinning:
		spinonFrames(co2, data1);
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

	Miles_SpinInit();

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