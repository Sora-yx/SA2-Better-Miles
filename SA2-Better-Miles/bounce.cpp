#include "stdafx.h"

bool rebound = false;

signed int Miles_CheckBounceAttack(CharObj2Base* a1, EntityData1* a2)
{
	if (!Action_Pressed[a1->PlayerNum] || !isBounce)
	{
		return 0;
	}
	a1->AnimInfo.Next = 66;
	a2->Action = Bounce;
	a2->Status |= Status_Attack | Status_Ball;
	a1->Speed.y = -5.0;
	rebound = false;
	//PlaySoundProbably(8202, 0, 0, 0);
	return 1;
}

signed int Miles_PerformBounce(CharObj2Base* a1, EntityData1* a2)
{
	if (!Action_Pressed[a1->PlayerNum] || !isBounce)
	{
		return 0;
	}
	a1->AnimInfo.Next = 66;
	a2->Status |= Status_Attack | Status_Ball;
	a2->Action = Bounce;
	a1->Speed.y = -7.0;
	//PlaySoundProbably(8202, 0, 0, 0);
	return 1;
}

static const void* const SetNextAnimPtr = (void*)0x474F80;
static inline int CheckSpeedAndSetNextAnim(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		call SetNextAnimPtr
		add esp, 4
		mov result, ebx
	}
	return result;
}

static const void* const  sub_4745D0ptr = (void*)0x4745D0;
static inline int sub_4745D0(CharObj2Base* a1, EntityData1* a2, EntityData2_R* a3)
{
	int result;
	__asm
	{
		push[a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_4745D0ptr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const  sub_474630ptr = (void*)0x474630;
static inline void sub_474630(CharObj2Base* a1, EntityData2_R* a2, EntityData1* a3)
{
	__asm
	{
		mov ebx, [a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_474630ptr
	}
}

float getGrav = 0.0;

void DoBounce(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2_R* data2) {
	if (Miles_CheckNextActions_r(data2, co2Miles, co2, data) || Tails_CheckActionWindowR(data, data2, co2, co2Miles)) {
		return;
	}
	if ((data->Status & 3) != 0)
	{
		data->Action = 70;
		data->Rotation.x = data2->ang_aim.x;
		data->Rotation.z = data2->ang_aim.z;
		if (rebound)
		{
			co2->Speed.y = 4.5999999;
		}
		else
		{
			co2->Speed.y = 3.5000001;
			rebound = true;
		}
		CallVibeThing(0, 15, co2->PlayerNum, 7);
		return;
	}
	if ((data->Status & 0x4000) != 0)
	{
		return;
	}
	if (!Jump_Pressed[co2->PlayerNum])
	{
		return;
	}
	getGrav = fabs(Gravity.y);
	if (getGrav == 1.0)
	{
		getGrav = fabs(co2->idk6 - data->Position.y); //distance max
		if (getGrav <= 8.0)
		{
			return;
		}
	}

	// sub_720E00(co2Miles, data, (EntityData2*)data2, co2);
	PlayVoice(2, 1629);
	co2->Speed.x = 4.0;
	data->Action = Flying;
	co2->AnimInfo.Next = FlyingAnim;
	data->Status &= 0xFEFFu;
	return;
}

void DoBounceOnFloor(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2_R* data2) {
	if (Miles_CheckNextActions_r(data2, co2Miles, co2, data) || Tails_CheckActionWindowR(data, data2, co2, co2Miles)) {
		return;
	}

	if ((data->Status & (Status_Unknown1 | Status_Ground)) != 0)
	{
		// PlaySoundProbably(v117, 0, 0, 0);

		if (CheckPlayerStop(data, co2, data2))
		{
			data->Rotation.x = data2->ang_aim.x;
			data->Rotation.z = data2->ang_aim.z;
			if (njScalor((const NJS_VECTOR*)&data2->spd) >= (double)1.0)
			{
				if (njScalor((const NJS_VECTOR*)&data2->spd) >= 2.5)
				{
					co2->AnimInfo.Next = 17;
					CallVibeThing(0, 15, co2->PlayerNum, 6);
				}
				else
				{
					co2->AnimInfo.Next = 16;
				}
				data->Status &= 0xFAFFu;
			}
			else
			{
				co2->AnimInfo.Next = 1;
				data->Status &= 0xFAFFu;
			}
		}
		else
		{
			data->Rotation.x = data2->ang_aim.x;
			data->Rotation.z = data2->ang_aim.z;
			data->Action = 1;
			CheckSpeedAndSetNextAnim(co2, data);
		}
	}
	else if ((data->Status & 0x4000) != 0
		|| (!Jump_Pressed[co2->PlayerNum])
		|| (getGrav = fabs(Gravity.y), getGrav == 1.0)
		&& (getGrav = fabs(co2->idk6 - data->Position.y), getGrav <= 8.0))
	{
		if (!Miles_PerformBounce(co2, data))
		{
			if (co2->AnimInfo.Next == 66 && co2->Speed.y <= 0.0)
			{
				co2->AnimInfo.Next = 67;
				data->Status &= 0xFEFFu;
			}
			if (sub_4745D0(co2, data, data2))
			{
				sub_474630(co2, data2, data);
				data->Status &= 0xFAFFu;
			}
		}
	}
	else
	{
		PlayVoice(2, 1629);
		co2->Speed.x = 4.0;
		data->Action = Flying;
		co2->AnimInfo.Next = FlyingAnim;
		data->Status &= 0xFEFFu;

		if (CurrentLevel != LevelIDs_GreenHill)
		{
			//bounce sound
		}
	}
	return;
}