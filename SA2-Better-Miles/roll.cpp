#include "stdafx.h"

signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2)
{
	if (Controllers[a2->PlayerNum].press & (Buttons_X | Buttons_B))
	{
		a1->Action = Rolling;
		a2->AnimInfo.Current = RollAnim;
		(a1->Status) |= Status_Ball; //BallForm
		//a2->SpindashSpeed = a2->Speed.x;
		return 1;
	}

	return 0;
}

void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2) {

	if (Controllers[co2->PlayerNum].press & (Buttons_X | Buttons_B))
	{
		data1->Action = Running;
		//co2->AnimationThing.Index = 36;
		(data1->Status) &= Status_Ball;
	}
}