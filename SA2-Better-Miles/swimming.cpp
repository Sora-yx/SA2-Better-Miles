#include "pch.h"

bool CheckWaterSurface(CharObj2Base* a1, EntityData1* a2)
{
	int v2; // eax
	bool result; // eax
	float v4; // [esp+0h] [ebp-4h]

	v2 = a1->PlayerNum;
	result = false;
	if ((!Action_Held[v2] || Jump_Pressed[v2])
		&& (a1->SurfaceInfo.TopSurface & SurfaceFlag_Water) != 0
		&& a2->Collision->CollisionArray->center.y < (double)a1->SurfaceInfo.TopSurfaceDist
		&& (a2->Status & 3) == 0)
	{
		v4 = fabs(a1->SurfaceInfo.TopSurfaceDist - a1->SurfaceInfo.BottomSurfaceDist);
		if (v4 > 7.0)
		{
			result = true;
		}
	}
	return result;
}

bool isSwimAllowed(TailsCharObj2* a1, EntityData1* a2)
{
	bool result; // eax
	float v3; // [esp+0h] [ebp-4h]

	result = false;

	if ((!Jump_Held[a1->base.PlayerNum] || a2->Action != 6 || a1->base.Speed.y <= 0.0)
		&& (a1->base.SurfaceInfo.TopSurface & 2) != 0
		&& (a2->Collision->CollisionArray->center.y + 4.0 < a1->base.SurfaceInfo.TopSurfaceDist || (a2->Status & 3) == 0))
	{
		v3 = fabs(a1->base.SurfaceInfo.TopSurfaceDist - a1->base.SurfaceInfo.BottomSurfaceDist);
		if (v3 > 7.0)
		{
			result = true;
		}
	}
	return result;
}

signed int Miles_SetNextActionSwim(TailsCharObj2* a1, EntityData1* a2)
{
	if (CurrentLevel == 90 || Action_Held[a1->base.PlayerNum] || !isSwimAllowed(a1, a2))
	{
		return 0;
	}
	a2->Action = FloatingOnWater;
	a1->base.AnimInfo.Next = 224;
	return 1;
}

void Miles_GetFloat(EntityData1* data, CharObj2Base* co2)
{
	double TopSurface; // st7
	double v3; // st7
	double result; // st7
	double rng; // st7
	EntityData2* data2; // eax
	float v7; // [esp+0h] [ebp-Ch]
	Float copyResult; // [esp+0h] [ebp-Ch]
	float posCalc; // [esp+4h] [ebp-8h]
	float posY; // [esp+8h] [ebp-4h]

	posY = data->Position.y - 1.0; //Used for Character surface position check. (Knuckles originally uses "+1.0", but since Miles is a bit smaller, we will got for -1.0.)
	posCalc = co2->PhysData.Height + data->Position.y + 10.0;
	TopSurface = co2->SurfaceInfo.TopSurfaceDist;
	if (posCalc >= TopSurface)
	{
		if (posY <= TopSurface)
		{
			result = (posCalc - TopSurface) * (co2->PhysData.Weight - 0.07999999821186066) * 0.1000000014901161
				+ (TopSurface - posY) * 0.02300000004470348
				- co2->Speed.y * 0.300000011920929;
		}
		else
		{
			result = co2->PhysData.Weight - 0.07999999821186066;
		}
	}
	else
	{
		v3 = co2->Speed.y;
		if (data->Action == Action_SwimMove)
		{
			result = 0.05999999865889549 - v3 * 0.03999999910593033;
		}
		else
		{
			result = 0.1599999964237213 - v3 * 0.09000000357627869;
		}
	}
	v7 = result;
	rng = (double)rand();
	data2 = MainCharData2[co2->PlayerNum];
	copyResult = rng * 0.000030517578125 * 0.00009999999747378752 + v7;
	data2->Acceleration.x = 0.0;
	data2->Acceleration.y = copyResult;
	data2->Acceleration.z = 0.0;
}

bool CheckWaterDistanceThing(CharObj2Base* a1)
{
	float v2; // [esp+0h] [ebp-4h]

	v2 = fabs(a1->SurfaceInfo.TopSurfaceDist - a1->SurfaceInfo.BottomSurfaceDist);
	return v2 > 7.0;
}

void CheckFloatingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (!Miles_CheckNextActions_r(data2, co2Miles, co2, data))
	{
		if ((co2->SurfaceInfo.TopSurface & SurfaceFlag_Water) == 0 || !CheckWaterDistanceThing(co2)) {
			data->Action = 0;
			co2->AnimInfo.Next = 1;
			PlaySoundProbably(28674, 0, 0, 0);
			return;
		}

		if (!Tails_CheckActionWindowR(data, data2, co2, co2Miles) && !TailsJump(co2, data))
		{
			if ((data->Status & 0x2000) == 0)
			{
				if (Action_Held[co2->PlayerNum])
				{
					data->Action = Diving;
					co2->AnimInfo.Next = 220;
					PlaySoundProbably(28675, 0, 0, 0);
					return;
				}

				if (GetAnalog(data, co2, 0, 0) || data->Status & Status_DisableControl) {
					data->Action = Swimming;
					co2->AnimInfo.Next = 219;
					return;
				}
			}
		}
	}
	return;
}

void CheckSwimmingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (!Miles_CheckNextActions_r(data2, co2Miles, co2, data))
	{
		if ((co2->SurfaceInfo.TopSurface & SurfaceFlag_Water) != 0 && CheckWaterDistanceThing(co2)) {
			if (!Tails_CheckActionWindowR(data, data2, co2, co2Miles) && !TailsJump(co2, data))
			{
				if ((!GetAnalog(data, co2, 0, 0)
					|| (data->Status & Status_DisableControl)))
				{
					data->Action = FloatingOnWater;
					co2->AnimInfo.Next = 222;
					return;
				}

				if (Action_Held[co2->PlayerNum])
				{
					data->Action = Diving;
					if (!isCustomAnim)
						co2->AnimInfo.Next = 15;
					else
						co2->AnimInfo.Next = 220;
					PlaySoundProbably(28675, 0, 0, 0);
					return;
				}
			}
		}
		else {
			data->Action = 1;
			co2->AnimInfo.Next = 4;
			PlaySoundProbably(28674, 0, 0, 0);
			return;
		}
	}
	return;
}

void CheckDivingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (!Miles_CheckNextActions_r(data2, co2Miles, co2, data))
	{
		if (CheckWaterSurface(co2, data))
		{
			data->Action = FloatingOnWater;
			if (!isCustomAnim)
				co2->AnimInfo.Next = 15;
			else
				co2->AnimInfo.Next = 222;
			return;
		}
		else if ((data->Status & 3) != 0)
		{
			if (Player_CheckBreakMaybe(0, data, co2) && co2->Speed.x < 0.0)
			{
				data->Action = 12;
				co2->AnimInfo.Next = 18;
				co2->AnimInfo.field_8 = 0;
				return;
			}
			else if (CheckPlayerStop(data, co2, data2))
			{
				data->Rotation.x = data2->Forward.x;
				data->Rotation.z = data2->Forward.z;
				if (njScalor(&data2->Velocity) >= 1.0)
				{
					if (njScalor(&data2->Velocity) >= 2.5)
					{
						co2->AnimInfo.Next = 17;
					}
					else
					{
						co2->AnimInfo.Next = 16;
					}
				}
				else
				{
					co2->AnimInfo.Next = 1;
				}
			}
			else
			{
				data->Rotation.x = data2->Forward.x;
				data->Rotation.z = data2->Forward.z;
				data->Action = 1;
				return;
			}
			PlaySoundProbably(28677, 0, 0, 0);
			data->Status &= 0xFAFFu;
		}
		else if (!Tails_CheckActionWindowR(data, data2, co2, co2Miles))
		{
			if (!Action_Held[co2->PlayerNum])
			{
				if ((!GetAnalog(data, co2, 0, 0)
					|| (data->Status & 0x2000) == 0))
				{
					data->Action = FloatingOnWater;
					if (!isCustomAnim)
						co2->AnimInfo.Next = 15;
					else
						co2->AnimInfo.Next = 222;
					return;
				}
				else
				{
					data->Action = Swimming;
					if (!isCustomAnim)
						co2->AnimInfo.Next = 15;
					else
						co2->AnimInfo.Next = 219;
					return;
				}
			}
		}
	}
	return;
}