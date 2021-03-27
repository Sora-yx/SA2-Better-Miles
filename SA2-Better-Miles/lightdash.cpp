#include "stdafx.h"

int lightdashTime = 0;
int lightdashTimer = 0;
Trampoline* RingMain_t;

static const void* const lightdashptr = (void*)0x7215D0;
static inline void Sonic_InitLightDashASM(EntityData1* data, CharObj2Base* co2, EntityData2_R* data2, TailsCharObj2* a5)
{
	__asm
	{
		push[a5]
		push[data2]
		mov eax, [co2]
		mov ecx, [data]
		call lightdashptr
		add esp, 8
	}
}

void Sonic_InitLightDash(EntityData1* data, CharObj2Base* co2, EntityData2_R* data2, TailsCharObj2* a5) {
	return Sonic_InitLightDashASM(data, co2, data2, a5);
}

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
		add esp, 4
		mov result, eax
	}
	return result;
}

void RingMain_R(ObjectMaster* obj)
{
	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 20))
	{
		if (Controllers[0].on & (Buttons_Y) && (MainCharObj1[0]->Action <= Running || MainCharObj1[0]->Action == Jumping || MainCharObj1[0]->Action == 10 || MainCharObj1[0]->Action == Flying)) {
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
	co2->Speed.x += 2.0 * 6.5;
	co2->Speed.y += 2.0 * 2.4;
	co2->Speed.z += 2.0 * 1.3;
	if (Call_sub_45B2C0(co2, getTimer, data1) < 2 || lightdashTimer <= 1)
	{
		njUnitVector(&co2->Speed);
		co2->Speed.x = co2->Speed.x * 2.0;
		co2->Speed.y = co2->Speed.y * 2.0;
		co2->Speed.z *= 2.0;
		goto LABEL_156;
	}
	else
	{
		co2->Speed.x = co2->PhysData.Run2;
		if (njScalor(&co2->Speed) > 0.0)
		{
			njUnitVector(&co2->Speed);
			co2->Speed.x *= co2->PhysData.Run2;
			co2->Speed.y = co2->PhysData.Run2 * co2->Speed.y;
			co2->Speed.z* co2->PhysData.Run2;
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
		add esp, 8
		mov result, eax
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

void InitLightDashStuff() {
	if (!isLightDash)
		return;

	RingMain_t = new Trampoline((int)RingMain, (int)RingMain + 0x6, RingMain_R);
}