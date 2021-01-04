#include "stdafx.h"


Trampoline* Tails_Main_t = nullptr;


static int Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3) { //rewrite this to remove "speed.y = 0.0" since writedata doesn't work.

	a1->Action = 59;
	a1->Status &= 0xDAFFu;
	a2->AnimInfo.Current = 90;
	a3->field_1BC[418] |= 1u;
	return PlayVoice(2, 1629);
}


int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3)
{
	__asm
	{
		push ecx // a3
		push edx // a2
		push eax // a1

		// Call your __cdecl function here:
		call Tails_FlyStart

		add esp, 4 // a1<eax> is also used for return value
		pop edx // a2
		pop ecx // a3
		retn
	}
}

void Tails_CheckGetAltitude(CharObj2Base* a1, EntityData1* a2, EntityData2_* a3)
{
	if (Controllers[a1->PlayerNum].on & Buttons_A) {
		if (a1->Speed.y < 1.5)
			a1->Speed.y += 0.08;
	}
}


void Miles_CheckLoseAltitude(CharObj2Base* a1, EntityData1* a2) {
	if (a2->Action != 59 || Controllers[a1->PlayerNum].on & Buttons_A || Controllers[a1->PlayerNum].press & Buttons_A)
		return;

	if (Controllers[a1->PlayerNum].on & (Buttons_X | Buttons_B))
	{
		if (a1->Speed.y > -9.0)
			a1->Speed.y -= 0.2;
	}
}


void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2) {

	if ((a2->Status & (Status_Unknown1 | Status_Ground)) == 0)
		return;

	unsigned __int16 v2; // ax
	AnimationIndex v3; // ebp
	__int16 v4; // ax
	__int16 v5; // ax
	__int16 v6; // ax
	float getMilesPosY;

	if (a2->Action == 60) {
		if (Controllers[a1->PlayerNum].on & (Buttons_B | Buttons_X)) {
			a2->Status &= 0xDAFFu;
			PlaySoundProbably(8202, 0, 0, 0);
		}
		else {
			a1->AnimInfo.Next = 0;
			a2->Action = 0;
		}
	}
}


void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	Miles_SpinAttack(MainCharObj2[0], MainCharObj1[0]);

	if (MainCharObj1[0]->Action == 59) {
		Tails_CheckGetAltitude(MainCharObj2[0], MainCharObj1[0], EntityData2Ptrs[0]);
		Miles_CheckLoseAltitude(MainCharObj2[0], MainCharObj1[0]);
	}
}


void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);


	//Spin Attack stuff
	WriteData<7>((int*)0x74ed0e, 0x90); //remove reset anim for spin attack
	WriteData<4>((int*)0x74ed0a, 0x90); //remove reset action for spin attack.

	WriteData<1>((int*)0xa0dbf2, 0x80); //Increase transition speed (from 0.125 to 1.0)
	WriteData<1>((int*)0xa0dbf3, 0x3F);
	WriteData<1>((int*)0xa0dbee, 0x5E);

	WriteData<5>((void*)0x752d9a, 0x90); //Remove tails voice when doing spin attack;


	//WriteData<1>((int*)0xa0dbf6, 0xC0);  //Animation Speed
	//WriteData<1>((int*)0xa0dbf7, 0x3F);*/

	//Improve physic
	PhysicsArray[Characters_Tails].AirAccel = 0.050;
	PhysicsArray[Characters_Tails].Brake = -0.25;
	PhysicsArray[Characters_Tails].HangTime = 60;
	PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
	PhysicsArray[Characters_Tails].GroundAccel = 0.14;

	//Remove the altitude nerf.
	WriteJump((void*)0x752DB0, Tails_FlyStartASM);


	//Increase Miles horizontal fly speed from 0.4 to 0.13
	WriteData<1>((int*)0x753045, 0x70);
	WriteData<1>((int*)0x753046, 0x63);
}