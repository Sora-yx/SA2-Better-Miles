#include "pch.h"
#include "abilities.h"

bool rebound = false;

signed int Miles_CheckBounceAttack(CharObj2Base* pwp, EntityData1* twp)
{
	if ((Controllers[pwp->PlayerNum].press & BounceBtn) == 0 || !isBounce)
	{
		return FALSE;
	}
	pwp->AnimInfo.Next = 66;
	twp->Action = Bounce;
	twp->Status |= Status_Attack | Status_Ball;
	pwp->Speed.y = -5.0f;
	rebound = false;
	//PlaySoundProbably(8202, 0, 0, 0);
	return TRUE;
}

signed int Miles_PerformBounce(CharObj2Base* pwp, EntityData1* twp)
{
	if ((Controllers[pwp->PlayerNum].press & BounceBtn) == 0 || !isBounce)
	{
		return FALSE;
	}
	pwp->AnimInfo.Next = 66;
	twp->Status |= Status_Attack | Status_Ball;
	twp->Action = Bounce;
	pwp->Speed.y = -7.0f;
	//PlaySoundProbably(8202, 0, 0, 0);
	return TRUE;;
}

float getGrav = 0.0f;

void DoBounce(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2* data2) {
	if (MilesCheckInput(data2, co2Miles, co2, data) || Tails_CheckActionWindow_(data, data2, co2, co2Miles)) {
		return;
	}
	if ((data->Status & 3) != 0)
	{
		data->Action = 70;
		data->Rotation.x = data2->Forward.x;
		data->Rotation.z = data2->Forward.z;
		if (rebound)
		{
			co2->Speed.y = 4.5999999f;
		}
		else
		{
			co2->Speed.y = 3.5000001f;
			rebound = true;
		}
		VibeThing(0, 15, co2->PlayerNum, 7);
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
	if (getGrav == 1.0f)
	{
		getGrav = fabs(co2->SurfaceInfo.BottomSurfaceDist - data->Position.y); //distance max
		if (getGrav <= 8.0f)
		{
			return;
		}
	}

	// sub_720E00(co2Miles, data, (EntityData2*)data2, co2);
	co2->Speed.x = 4.0f;
	Tails_FlyStart(data, co2, co2Miles);
	data->Status &= 0xFEFFu;
	return;
}

void DoBounceOnFloor(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2* data2) {
	if (MilesCheckInput(data2, co2Miles, co2, data) || Tails_CheckActionWindow_(data, data2, co2, co2Miles)) {
		return;
	}

	if ((data->Status & (Status_OnObjectColli | Status_Ground)) != 0)
	{
		// PlaySoundProbably(v117, 0, 0, 0);

		if (PlayerStop(data, co2, data2))
		{
			data->Rotation.x = data2->Forward.x;
			data->Rotation.z = data2->Forward.z;
			if (njScalor((const NJS_VECTOR*)&data2->Velocity) >= 1.0f)
			{
				if (njScalor((const NJS_VECTOR*)&data2->Velocity) >= 2.5f)
				{
					co2->AnimInfo.Next = 17;
					VibeThing(0, 15, co2->PlayerNum, 6);
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
			data->Rotation.x = data2->Forward.x;
			data->Rotation.z = data2->Forward.z;
			data->Action = 1;
			PlayerChangeRunningMotion(co2, data);
			data->Status &= 0xFAFFu;
		}
	}
	else if ((data->Status & 0x4000) != 0
		|| (!Jump_Pressed[co2->PlayerNum])
		|| (getGrav = fabs(Gravity.y), getGrav == 1.0f)
		&& (getGrav = fabs(co2->SurfaceInfo.BottomSurfaceDist - data->Position.y), getGrav <= 8.0f))
	{
		if (!Miles_PerformBounce(co2, data))
		{
			if (co2->AnimInfo.Next == 66 && co2->Speed.y <= 0.0f)
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
		co2->Speed.x = 4.0f;
		Tails_FlyStart(data, co2, co2Miles);
		data->Status &= 0xFEFFu;

		if (CurrentLevel != LevelIDs_GreenHill)
		{
			//bounce sound
		}
	}
	return;
}