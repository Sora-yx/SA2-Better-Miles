#include "stdafx.h"

float TailsFlightTime = 0.0000000000; //fatigue
double flyCustomSpeedValue = 0.11; //used to improve Miles flight speed

static int Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3) { //rewrite the function to remove the vertical speed nerf since writedata doesn't work.
	a1->Action = Flying;
	a1->Status &= 0xDAFFu;
	a2->AnimInfo.Current = FlyingAnim;
	a3->field_1BC[418] |= 1u; //idk
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
		if (TailsFlightTime < 1.0) {

			if (!isInfiniteFly)
				TailsFlightTime += 0.0043333338;

			if ((a1->Upgrades & Upgrades_SuperSonic) && a1->Speed.y < 2.7)
				a1->Speed.y += 0.3;
			else if (a1->Speed.y < 1.2)
				a1->Speed.y += 0.03;
		}
	}
}


void Miles_CheckLoseAltitude(CharObj2Base* a1, EntityData1* a2) {
	if (a2->Action != Flying || Controllers[a1->PlayerNum].on & Buttons_A || Controllers[a1->PlayerNum].press & Buttons_A || TailsFlightTime >= 1.0)
		return;

	if (Controllers[a1->PlayerNum].on & (Buttons_X | Buttons_B))
	{
		if (a1->Speed.y > -9.0)
			a1->Speed.y -= 0.14;
	}
}

void Tails_FatigueReloadCheck(EntityData1* data1) {

	if (data1->Action == Flying || TailsFlightTime == 0.0000000000)
		return;

	if ((data1->Status & (Status_Unknown1 | Status_Ground)) || MainCharObj1[0]->Action < Flying) {

		TailsFlightTime = 0.0000000000;
	}
}

void Tails_Fatigue(EntityData1* data1, CharObj2Base* co2) {

	if (TailsFlightTime >= 1.0) {
		if (co2->Speed.y > -8.0)
			co2->Speed.y -= 0.13;
	}
}


void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2) {

    if (data1->Action == Flying && TailsFlightTime < 1.0) {
        Tails_CheckGetAltitude(co2, data1, data2);
        Miles_CheckLoseAltitude(co2, data1);
    }

    if (!isInfiniteFly) {
        Tails_FatigueReloadCheck(data1);
        Tails_Fatigue(data1, co2);
    }
}


void Init_MilesFly() {

	WriteJump((void*)0x752DB0, Tails_FlyStartASM); 	//Remove the altitude nerf.
	MilesFlySpeedValue = flyCustomSpeedValue; //asign a new value for horizontal fly speed.
}