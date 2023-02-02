#include "pch.h"

int lightdashTime = 0;
int lightdashTimer = 0;
Trampoline* RingMain_t = nullptr;
NJS_VECTOR LightDashPos = { 0 };

void Miles_PerformLightDash(CharObj2Base* co2, EntityData1* data)
{
	data->Action = LightDash;
	if (isCustomAnim)
		co2->AnimInfo.Next = LightdashAnim;
	else
		co2->AnimInfo.Next = 4;
	lightdashTime = 10;
	lightdashTimer = 0;
	co2->Speed.x = 16.0;
	data->Status = data->Status & ~Status_Ball | Status_Attack;
	PlaySoundProbably(8210, 0, 0, 0);
}


void RingMain_R(ObjectMaster* obj)
{
	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 25))
	{
		if ( (Controllers[0].on & LightDashBtn) && (MainCharObj1[0]->Action <= Running || MainCharObj1[0]->Action == Jumping || MainCharObj1[0]->Action == 10 || MainCharObj1[0]->Action == Flying)) 
		{
			DoNextAction_r(0, 103, 0);
		}
	}

	ObjectFunc(origin, RingMain_t->Target());
	origin(obj);
}

void CheckLightDashEnd(TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1) 
{
	int lightdashTimee = lightdashTime;
	int getTimer = lightdashTimee - 1;
	lightdashTime = lightdashTimee - 1;
	NJS_VECTOR vecIDK;

	if (lightdashTimee > 0)
	{
		if (++lightdashTimer <= 360)
		{
			CollisionInfo* col = (CollisionInfo*)data1->Collision->CollidingObject;
			if (col)
			{
				ObjectMaster* idkOBJ = col->Object;

				if (idkOBJ)
				{
					char IDThing = idkOBJ->Data1.Entity->field_2;
					if (IDThing == 21)
					{
						data1->Action = 10;
						co2->AnimInfo.Next = 15;
						co2->Speed.x = 0.0;
						lightdashTime = 0;
						data1->Status &= 0xFBFFu;
						//PlaySound3(-1025, 8210);
						return;
					}
				}
			}
			GetBufferedPositionAndRot(co2->PlayerNum, 0, &vecIDK, 1);

			if (CheckDistance(&data1->Position, &vecIDK) <= 1.5f)
			{
				data1->Action = 12;
				bool spd = co2->Speed.x > 2.0f;
				co2->AnimInfo.Next = 18;
				co2->AnimInfo.field_8 = 0;
				if (spd)
				{
					co2->Speed.x = 2.0f;
				}
				else {
					co2->Speed.x += 2.0f;
				}
				data1->Status &= 0xFBFFu;
				lightdashTime = 0;
				//PlaySound3(0, 8210);
			}
			
			return;
		}
	}

	data1->Action = 10;
	co2->AnimInfo.Next = 15;
	co2->Speed.x += 2.0f * 6.5f;
	co2->Speed.y += 2.0f * 2.4f;
	co2->Speed.z += 2.0f * 1.3f;

	if (sub_45B2C0(co2, getTimer, data1) < 2 || lightdashTimer <= 1)
	{
		njUnitVector(&co2->Speed);
		co2->Speed.x *= 2.0f;
		co2->Speed.y *= 2.0f;
		co2->Speed.z *= 2.0f;
	}
	else
	{
		co2->Speed.x = co2->PhysData.DashSpeed;
		if (njScalor(&co2->Speed) > 0.0f)
		{
			njUnitVector(&co2->Speed);
			co2->Speed.x *= co2->PhysData.DashSpeed;
			co2->Speed.y *= co2->PhysData.DashSpeed;
			co2->Speed.z *= co2->PhysData.DashSpeed;
		}
	}

	co2->Speed.z *= co2->PhysData.DashSpeed;
	lightdashTime = 0;
	data1->Status &= 0xFBFFu;
	//PlaySound3(0, 8210);
	return;
}


void CheckRefreshLightDashTimer(CharObj2Base* co2, EntityData1* data) {
	HomingAttackTarget* v6 = sub_721480(co2, data, 32.0);
	if (v6)
	{
		if (lightdashTime < 5)
		{
			lightdashTime = 5;
		}
	}
	else {
		if (lightdashTimer <= 1 && !sub_721480(co2, data, 64.0f))
		{
			if (njScalor(&co2->Speed) > 2.0f)
			{
				njUnitVector(&co2->Speed);
				/**co2->Speed.x *= 2.0f;
				co2->Speed.y *= 2.0f;
				co2->Speed.z *= 2.0f;*/
				co2->Speed.x *= co2->PhysData.DashSpeed;
				co2->Speed.y *= co2->PhysData.DashSpeed;
				co2->Speed.z *= co2->PhysData.DashSpeed;
			}
			lightdashTime = 0;
		}
	}
}

void InitLightDashStuff() {
	if (!isLightDash)
		return;

	RingMain_t = new Trampoline((int)RingMain, (int)RingMain + 0x6, RingMain_R);
}