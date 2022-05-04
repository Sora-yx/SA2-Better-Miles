#include "pch.h"

float TailsFlightTime = 0.0000000000; //fatigue
double flyCustomSpeedValue = 0.11; //used to improve Miles flight speed

static void Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3) { //rewrite the function to remove the vertical speed nerf since writedata doesn't work.

	if (TailsFlightTime >= 1.0 && !isInfiniteFly)
		return;

	a1->Action = Flying;
	a1->Status &= 0xDAFFu;
	a2->AnimInfo.Current = FlyingAnim;
	a3->field_1BC[418] |= 1u; //idk

	if (!isTailsAI())
		PlayVoice(2, 1629);

	return;
}

static void __declspec(naked) Tails_FlyStartASM()
{
	__asm
	{
		push ecx
		push edx
		push eax
		call Tails_FlyStart
		add esp, 4 
		pop edx
		pop ecx
		retn
	}
}

void Tails_CheckGetAltitude(CharObj2Base* a1)
{
	if (Controllers[a1->PlayerNum].on & Buttons_A) {
		if (TailsFlightTime < 1.0) {

			if (!isInfiniteFly && !isSuperForm(a1->PlayerNum))
				TailsFlightTime += 0.0043333338;

			if (isSuperForm(a1->PlayerNum) && a1->Speed.y < 4.0)
				a1->Speed.y += 0.20;
			else if (a1->Speed.y < 1.2)
				a1->Speed.y += 0.03;
		}
	}
}

void Miles_CheckLoseAltitude(CharObj2Base* a1, EntityData1* a2) {

	if (a2->Action != Flying || Action_Held[a1->PlayerNum] || Action_Pressed[a1->PlayerNum] || TailsFlightTime >= 1.0)
		return;

	if (Action_Held[a1->PlayerNum])
	{
		if (isSuperForm(a1->PlayerNum) && a1->Speed.y > -9.0)
			a1->Speed.y -= 0.20;
		else if (a1->Speed.y > -9.0)
			a1->Speed.y -= 0.14;
	}
}

void Tails_FatigueReloadCheck(EntityData1* data1) {
	if (data1->Action == Flying || TailsFlightTime == 0.0000000000)
		return;

	if ((data1->Status & (Status_OnObjectColli | Status_Ground))) {
		TailsFlightTime = 0.0000000000;
	}
}

void Tails_Fatigue(EntityData1* data1, CharObj2Base* co2) {

	if (TailsFlightTime >= 1.0) {
		if (data1->Action != Action_Fall) {
			data1->Action = Action_Fall;
			co2->AnimInfo.Next = 91;

			if (!isTailsAI())
				PlayCustomSoundVolume(Voice_TailsTired, 1);

			return;
		}
	}
}


void MilesFly(EntityData1* data1, CharObj2Base* co2) {
	if (data1->Action == Flying && TailsFlightTime < 1.0) {
		Tails_CheckGetAltitude(co2);
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