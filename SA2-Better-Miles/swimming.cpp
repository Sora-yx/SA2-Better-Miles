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
	bool result; 
	float v3; 

	result = false;

	if ((!Jump_Held[a1->base.PlayerNum] || a2->Action != 6 || a1->base.Speed.y <= 0.0f)
		&& (a1->base.SurfaceInfo.TopSurface & 2) != 0
		&& (a2->Collision->CollisionArray->center.y + 4.0f < a1->base.SurfaceInfo.TopSurfaceDist || (a2->Status & 3) == 0))
	{
		v3 = fabs(a1->base.SurfaceInfo.TopSurfaceDist - a1->base.SurfaceInfo.BottomSurfaceDist);
		if (v3 > 7.0f)
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
	a2->Status &= ~Status_Ball;
	a2->Action = FloatingOnWater;
	a1->base.AnimInfo.Next = 224;
	return 1;
}

void Miles_GetFloat(EntityData1* data, CharObj2Base* co2)
{

	Float result = 0.0f;
	Float posY = data->Position.y - 1.0f; //Used for Character surface position check. (Knuckles originally uses "+1.0", but since Miles is a bit smaller, we will got for -1.0.)
	Float posCalc = co2->PhysData.Height + data->Position.y + 10.0f;
	Float TopSurface = co2->SurfaceInfo.TopSurfaceDist;
	if (posCalc >= TopSurface)
	{
		if (posY <= TopSurface)
		{
			result = (posCalc - TopSurface) * (co2->PhysData.Weight - 0.07999999821186066) * 0.1000000014901161
				+ (TopSurface - posY) * 0.02300000004470348f
				- co2->Speed.y * 0.300000011920929f;
		}
		else
		{
			result = co2->PhysData.Weight - 0.07999999821186066f;
		}
	}
	else
	{
		Float spdY = co2->Speed.y;
		if (data->Action == Action_SwimMove)
		{
			result = 0.05999999865889549f - spdY * 0.03999999910593033f;
		}
		else
		{
			result = 0.1599999964237213f - spdY * 0.09000000357627869f;
		}
	}

	EntityData2* data2 = MainCharData2[co2->PlayerNum];
	Float accY = rand() * 0.000030517578125f * 0.00009999999747378752f + result;
	data2->Acceleration.x = 0.0f;
	data2->Acceleration.y = accY;
	data2->Acceleration.z = 0.0f;
}

bool CheckWaterDistanceThing(CharObj2Base* a1)
{
	Float dist = fabs(a1->SurfaceInfo.TopSurfaceDist - a1->SurfaceInfo.BottomSurfaceDist);
	return dist > 7.0f;
}

void CheckFloatingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (!MilesCheckInput(data2, co2Miles, co2, data))
	{
		if ((co2->SurfaceInfo.TopSurface & SurfaceFlag_Water) == 0 || !CheckWaterDistanceThing(co2)) {
			data->Action = 0;
			co2->AnimInfo.Next = 1;
			PlaySoundProbably(28674, 0, 0, 0);
			return;
		}

		if (!Tails_CheckActionWindow_(data, data2, co2, co2Miles) && !TailsJump(co2, data))
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
	if (!MilesCheckInput(data2, co2Miles, co2, data))
	{
		if ((co2->SurfaceInfo.TopSurface & SurfaceFlag_Water) != 0 && CheckWaterDistanceThing(co2)) {
			if (!Tails_CheckActionWindow_(data, data2, co2, co2Miles) && !TailsJump(co2, data))
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
	if (!MilesCheckInput(data2, co2Miles, co2, data))
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
			if (PlayerCheckBreak(0, data, co2) && co2->Speed.x < 0.0)
			{
				data->Action = 12;
				co2->AnimInfo.Next = 18;
				co2->AnimInfo.field_8 = 0;
				return;
			}
			else if (PlayerStop(data, co2, data2))
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
		else if (!Tails_CheckActionWindow_(data, data2, co2, co2Miles))
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