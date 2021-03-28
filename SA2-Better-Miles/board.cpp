#include "stdafx.h"


static const void* const sub_45E300Ptr = (void*)0x45E300;
static inline int sub_45E300ASM(CharObj2Base* a1, EntityData1* a2, EntityData2_R* a3, float a4)
{
	int result;
	__asm
	{
		push[a4]
		push[a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_45E300Ptr
		add esp, 8
		mov result, eax
	}
	return result;
}

int PhysicsBoardStuff(CharObj2Base* a1, EntityData1* a2, EntityData2_R* a3, float a4) {
	return sub_45E300ASM(a1, a2, a3, a4);
}

static const void* const boardPtr = (void*)0x727540;
static inline void BoardSparklesMaybeASM(EntityData2_R* a1, EntityData1* a2, TailsCharObj2* a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call boardPtr
		add esp, 8
	}
}

void BoardSparklesMaybe(EntityData2_R* a1, EntityData1* a2, TailsCharObj2* a3) {
	return BoardSparklesMaybeASM(a1, a2, a3);
}

static const void* const sub_45E9A0Ptr = (void*)0x45E9A0;
static inline float sub_45E9A0(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
	float result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, a1
		call sub_45E9A0Ptr
		add esp, 8
		fstp result
	}
	return result;
}

float PhysicsBoardStuff2(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3) {
	return sub_45E9A0(a1, a2, a3);
}


void BoardStuff(EntityData2_R* data2, TailsCharObj2* co2Miles, EntityData1* data, CharObj2Base* co2) {

	if (Miles_CheckNextActions_r(data2, co2Miles, co2, data))
	{
		return;
	}

	if (Jump_Pressed[co2->PlayerNum])
	{
		data->Action = 80;
		co2->Speed.y = co2->PhysData.JumpSpeed;
		co2->AnimInfo.Next = 127;
		if (co2->PhysData.Run1 > co2->Speed.x) //rushspeed
		{
			co2->Speed.x = co2->PhysData.RollCancel + co2->Speed.x; //jogspeed
		}
	}

	return;
}


void BoardJumpStuff(EntityData1* data, CharObj2Base* co2, EntityData2_R* data2) {

	if ((data->Status & 3) != 0)
	{
		data->Action = 76;
		co2->AnimInfo.Next = 121;
		co2->AnimInfo.field_10 = 0.0;
		if (co2->Speed.x <= 0.30000001)
		{
			co2->Speed.x = 1.0;
		}
		;
		data->Rotation.x = data2->ang_aim.x;
		data->Rotation.z = data2->ang_aim.z;
		if (CurrentLevel == 13 || CurrentLevel == 52)
		{
			Play3DSoundPosThing(0, &data->Position, 0, 0, -10);
		}
		return;
	}
	if (co2->Speed.y <= 0.0 && co2->AnimInfo.Current == 127)
	{
		co2->AnimInfo.Next = 128;
	}

	return;

}