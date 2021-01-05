#include "stdafx.h"


Trampoline* Tails_Main_t = nullptr;

static const void* const GetAnalogPtr2 = (void*)0x45A870;

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
}



void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2_* data2 = EntityData2Ptrs[0];


	if (data1->Action <= 2)
		Miles_CheckSpinAttack(data1, co2);

	MilesFly(data1, co2, data2);
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

	//Remove the altitude nerf.
	WriteJump((void*)0x752DB0, Tails_FlyStartASM);

	//Increase Miles horizontal fly speed from 0.4 to 0.12
	WriteData<1>((int*)0x753045, 0xE8);
	WriteData<1>((int*)0x753046, 0x50);
}