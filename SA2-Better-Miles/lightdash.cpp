#include "stdafx.h"

int lightdashTime = 0;
int lightdashTimer = 0;
Trampoline* RingMain_t;



void DoNextAction_r(int playerNum, char action, int unknown)
{
	EntityData1* v3; // eax

	v3 = MainCharObj1[playerNum];
	if (v3)
	{
		v3->Status |= Status_DoNextAction;
		v3->NextAction = action;
		MainCharObj2[playerNum]->field_28 = unknown;
	}
}

void Miles_PerformLightDash(CharObj2Base* co2, EntityData1* data)
{
	data->Action = LightDash;
	co2->AnimInfo.Next = 87;
	lightdashTime = 10;
	lightdashTimer = 0;
	co2->Speed.x = 16.0;
	data->Status = data->Status & ~Status_Ball | Status_Attack;
	PlaySoundProbably(8210, 0, 0, 0);
}


static const void* const GetBufferedPositionAndRotPtr = (void*)0x46DBF0;
static inline signed int GetBufferedPositionAndRot(int a1, int a2, NJS_VECTOR* a3, char a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a3]
		mov edi, [a2]
		mov eax, [a1]
		call GetBufferedPositionAndRotPtr
		mov result, eax
	}
	return result;
}


void RingMain_R(ObjectMaster* obj)
{

	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 15))
	{
		if (Controllers[0].on & (Buttons_Y)) {
			DoNextAction_r(0, 103, 0);
		}
	}

	ObjectFunc(origin, RingMain_t->Target());
	origin(obj);
}

void CheckLightDashEnd(TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1) {


	int lightdashTimee = lightdashTime;
	int getTimer = lightdashTimee - 1;
	lightdashTime = lightdashTimee - 1;
	NJS_VECTOR vecIDK;
	if (lightdashTimee > 0)
	{
		int timer = lightdashTimer;
		lightdashTimer = timer + 1;
		if (timer <= 360)
		{
			CollisionInfo* col = (CollisionInfo*)data1->Collision->field_A4;
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
					if (IDThing == 17)
					{
						int v49 = lightdashTimer;

						if (v49 >= 1)
						{
							if (CheckDistance(&idkOBJ->Data1.Entity->Position, (NJS_VECTOR*)&co2Miles->field_1BC[456]) > 0.5)
							{
								lightdashTimer++;
							}
						}
						else
						{
							lightdashTimer = v49 + 1;
						}
					}
				}
			}
			GetBufferedPositionAndRot(co2->PlayerNum, 0, &vecIDK, 1);
			if (CheckDistance(&data1->Position, &vecIDK) <= 1.5)
			{
				data1->Action = 12;
				float v55 = co2->Speed.x > 2.0;
				co2->AnimInfo.Next = 18;
				co2->AnimInfo.field_8 = 0;
				if (v55)
				{
					co2->Speed.x = 2.0;
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
	if (Call_sub_45B2C0(co2, getTimer, data1) < 2 || lightdashTimer <= 1)
	{
		NJS_VECTOR* v59 = &co2->Speed;
		if (njScalor(&co2->Speed) > 2.0)
		{
			njUnitVector(v59);
			v59->x = v59->x * 2.0;
			co2->Speed.y = co2->Speed.y * 2.0;
			co2->Speed.z *= 2.0;
			goto LABEL_156;
		}
	}
	else
	{

		co2->Speed.x = co2->PhysData.Run2;
		if (njScalor(&co2->Speed) > 0.0)
		{
			njUnitVector(&co2->Speed);
			co2->Speed.x *= co2->PhysData.Run2;
			co2->Speed.y = co2->PhysData.Run2 * co2->Speed.y;
			co2->Speed.z * co2->PhysData.Run2;
		LABEL_156:
			co2->Speed.z *= co2->PhysData.Run2;
			goto LABEL_157;
		}
	}
LABEL_157:
	lightdashTime = 0;
	data1->Status &= 0xFBFFu;
	//PlaySound3(0, 8210);
	return;
}


void __fastcall njAddVector(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x + vs->x;
	vd->y = vs->y + vd->y;
	vd->z = vs->z + vd->z;
}

void __fastcall njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x - vs->x;
	vd->y = vd->y - vs->y;
	vd->z = vd->z - vs->z;
}

int __cdecl BAMS_SubWrap(__int16 bams_a, unsigned __int16 bams_b, int limit)
{
	int result; // eax
	__int16 v4; // cx

	result = bams_b;
	v4 = bams_b - bams_a;
	if ((__int16)(bams_b - bams_a) > limit || v4 < -limit)
	{
		if (v4 >= 0)
		{
			result = (unsigned __int16)(limit + bams_a);
		}
		else
		{
			result = (unsigned __int16)(bams_a - limit);
		}
	}
	return result;
}

static const void* const PConvertVPtr = (void*)0x468DF0;
static inline void PConvertVector_G2PASM(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1]
		call PConvertVPtr
		add esp, 8
	}
}


static const void* const sub721480ptr = (void*)0x721480;
static inline HomingAttackTarget* sub_721480(CharObj2Base* a1, EntityData1* a2, float a3)
{
	HomingAttackTarget* result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call sub721480ptr
		mov result, eax
		add esp, 8
	}
	return result;
}

int sub_446960(int result, int a2, __int16 a3)
{
	result = (unsigned __int16)result;
	if ((__int16)(result - a3) > a2 || (__int16)(result - a3) < -a2)
	{
		if ((((WORD)result - a3) & 0x8000) != 0)
		{
			result = (unsigned __int16)(a3 - a2);
		}
		else
		{
			result = (unsigned __int16)(a3 + a2);
		}
	}
	return result;
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

		if (lightdashTimer <= 1 && !sub_721480(co2, data, 64.0))
		{

			if (njScalor(&co2->Speed) > 2.0)
			{
				njUnitVector(&co2->Speed);
				co2->Speed.x = co2->Speed.x * 2.0;
				co2->Speed.y = co2->Speed.y * 2.0;
				co2->Speed.z = 2.0 * co2->Speed.z;
			}
			lightdashTime = 0;
		}
	}
}

void __cdecl Miles_InitLightDash(EntityData1* data, EntityData2_R* data2, CharObj2Base* co2)
{
	HomingAttackTarget* v6; // eax
	NJS_VECTOR* v7; // esi
	EntityData1* v8; // ecx
	CollisionData* v9; // edx
	double v10; // st7
	float v11; // eax
	float v12; // ecx
	NJS_VECTOR* v13; // eax
	double v14; // st7
	int v15; // ecx
	int v16; // eax
	Float v17; // edx
	Float v18; // eax
	Float v19; // edx
	Float v20; // eax
	float v21; // [esp+14h] [ebp-14h]
	float v22; // [esp+14h] [ebp-14h]
	float v23; // [esp+14h] [ebp-14h]
	float v24; // [esp+18h] [ebp-10h]
	float v25; // [esp+18h] [ebp-10h]
	NJS_VECTOR a1a; // [esp+1Ch] [ebp-Ch] BYREF

	v6 = sub_721480(co2, data, 32.0);
	if (v6)
	{
		v8 = v6->entity;
		v21 = v6->distance;
		v9 = v6->entity->Collision->CollisionArray;
		if (lightdashTime < 5)
		{
			lightdashTime = 5;
		}
		a1a.x = v8->Position.x;
		v10 = a1a.x + v9->center.x;
		v11 = v8->Position.y;
		v12 = v8->Position.z;
		a1a.y = v11;
		a1a.x = v10;
		a1a.z = v12;
		a1a.y = v9->center.y + v11;
		v13 = &data->Collision->CollisionArray->center;
		a1a.z = v9->center.z + v12;
		a1a.x = a1a.x - v13->x;
		a1a.y = a1a.y - v13->y;
		a1a.z = a1a.z - v13->z;
		v24 = atan2(a1a.x, a1a.z);
		v14 = 0.0;
		v15 = (int)(v24 * 10430.38043493439);
		if (Gravity.y > 0.0)
		{
			v15 = 0x8000 - v15;
		}
		v16 = sub_446960(v15, 6144, data->Rotation.y);
		data->Rotation.y = v16;
		data2->ang_aim.y = v16;
		if (v21 > 0.0)
		{
			v14 = v21;
		}
		v22 = v14;
		v25 = sqrt(v22);
		v23 = v25;
		if (v25 <= 16.0)
		{
			if (v25 < 2.0)
			{
				v23 = 2.0;
			}
		}
		else
		{
			v23 = 16.0;
		}
		if (njScalor(&a1a) <= (double)1.0)
		{
			v17 = data2->spd.y;
			v18 = data2->spd.z;
			a1a.x = data2->spd.x;
			a1a.y = v17;
			a1a.z = v18;
		}
		njUnitVector(&a1a);
		data2->spd.x = a1a.x * v23;
		data2->spd.y = a1a.y * v23;
		data2->spd.z = v23 * a1a.z;
		PConvertVector_G2PASM(data, &a1a);
		v19 = a1a.y;
		v20 = a1a.z;
		co2->Speed.x = a1a.x;
		co2->Speed.y = v19;
		co2->Speed.z = v20;
	}
	else
	{
		if (lightdashTimer <= 1 && !sub_721480(co2, data, 64.0))
		{
			v7 = &co2->Speed;
			if (njScalor(&co2->Speed) > 2.0)
			{
				njUnitVector(v7);
				v7->x = v7->x * 2.0;
				co2->Speed.y = co2->Speed.y * 2.0;
				co2->Speed.z = 2.0 * co2->Speed.z;
			}
			lightdashTime = 0;
		}
		SlowDownThing_r(data, data2, co2);
		PlayerGetSpeed(data, co2, data2);
	}
}

void InitLightDashStuff() {

	RingMain_t = new Trampoline((int)RingMain, (int)RingMain + 0x6, RingMain_R);
}