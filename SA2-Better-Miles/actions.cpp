#include "stdafx.h"

Trampoline* CheckBreakObject_t;
Trampoline* MysticMelody_t;


static const void* const GetAnalogPtr2 = (void*)0x45A870;
inline int GetAnalogASM2(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude)
{

	int result;
	__asm
	{
		push[magnitude]
		push[angle]
		push[co2]
		mov eax, [data]
		call GetAnalogPtr2
		mov result, eax
		add esp, 12
	}
	return result;
}

signed int CallGetAnalog(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude) {
	return GetAnalogASM2(data, co2, angle, magnitude);
}


static const void* const VibeThingPtr = (void*)0x438E70;
static void __declspec(naked) VibeThingASM(int a1, signed int a2, int a3, signed int a4)
{
	__asm
	{
		push[esp + 04h] // int a4
		push ecx // a3
		push edx // int a2
		push eax // a1

		// Call your __cdecl function here:
		call VibeThingPtr

		pop eax // a1
		pop edx // int a2
		pop ecx // a3
		add esp, 4 // int a4
		retn
	}
}

void CallVibeThing(int a1, signed int a2, int a3, signed int a4)
{
	VibeThingASM(a1, a2, a3, a4);
	return;
}


signed char GetCharacterLevel() {

	for (int i = 0; i < 33; i++)
	{
		if (CurrentLevel == StageSelectLevels[i].Level)
		{
			return StageSelectLevels[i].Character;
		}
	}

	return -1;
}



bool isMilesAttacking() {

	if (MainCharObj2[0]->CharID != Characters_Tails)
		return false;

	EntityData1* data1 = MainCharObj1[0];

	if (data1->Action == Flying || data1->Action == Jumping || data1->Action == Spinning || data1->Action == Rolling)
		return true;

	return false;
}


Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];

	if (isMilesAttacking() && GetCollidingPlayer(obj))
		return 1;

	FunctionPointer(Bool, original, (ObjectMaster* obj, ObjectMaster* other), CheckBreakObject_t->Target());
	return original(obj, other);
}


static const void* const loc_776339 = (void*)0x776339;
__declspec(naked) void  CheckBreakCGGlasses() {

	if (MainCharObj1[0]->Action == 13 || isMilesAttacking())
	{
		_asm jmp loc_776339
	}
}


static const void* const loc_6d6934 = (void*)0x6d6934;
__declspec(naked) void  CheckBreakIronBox() {

	if (MainCharObj2[0]->CharID == Characters_Tails || MainCharObj2[0]->Upgrades & Upgrades_SonicFlameRing != 0)
	{
		_asm jmp loc_6d6934
	}
}


static const void* const sub_46EE00ptr = (void*)0x46EE00;
signed int CheckUpgradeBox(ObjectMaster* a1) {

	if (isMilesAttacking() && MainCharObj2[0]->CharID == Characters_Tails)
		return 1;
	else {
		_asm call sub_46EE00ptr
	}
}

static void __declspec(naked) sub_46EE00()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call CheckUpgradeBox

		add esp, 4 // a1<eax> is also used for return value
		retn
	}
}

static const void* const sub_475F00ptr = (void*)0x475F00;
static void __declspec(naked) SetMysticMelodyAction(CharObj2Base* a1, EntityData1* a2)
{
	__asm
	{
		push ecx // a2
		push eax // a1

		// Call your __cdecl function here:
		call  sub_475F00ptr

		pop eax // a1
		pop ecx // a2
		retn
	}
}

int __cdecl IsPlayerInsideSphere(NJS_VECTOR* x_1, float radius)
{
	float v2; // edx
	float v3; // eax
	int v4; // esi
	EntityData1* v5; // eax
	CollisionInfo* v6; // eax
	float* v7; // eax
	double v8; // st7
	float v10; // [esp+4h] [ebp-14h]
	float v11; // [esp+8h] [ebp-10h]
	NJS_VECTOR v; // [esp+Ch] [ebp-Ch] BYREF
	float v13; // [esp+1Ch] [ebp+4h]

	v2 = x_1->y;
	v3 = x_1->z;
	v13 = x_1->x;
	v10 = v2;
	v11 = v3;
	v4 = 0;
	while (1)
	{
		v5 = MainCharObj1[v4];
		if (v5)
		{
			v6 = v5->Collision;
			if (v6)
			{
				v7 = (float*)&v6->CollisionArray->center;
				v8 = v7[2];
				// pointer to Y of the first vector because sega hates everything
				v7 += 3;
				v.x = v8 - v13;
				v.y = *v7 - v10;
				v.z = v7[1] - v11;
				if (njScalor(&v) - radius < 0.0)
				{
					break;
				}
			}
		}
		if (++v4 >= 2)
		{
			return 0;
		}
	}
	return v4 + 1;
}

EntityData2_* PlayMysticMelody(ObjectMaster* obj)
{
	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data = MainCharObj1[0];

	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 30))
	{
		if (Controllers[co2->PlayerNum].on & (Buttons_X | Buttons_B))
			SetMysticMelodyAction(co2, data);
	}

	ObjectFunc(origin, MysticMelody_t->Target());
	origin(obj);
}


static const void* const loc_776D2A = (void*)0x776d23;
__declspec(naked) void  CheckGravitySwitch() {

	if (MainCharObj1[0]->Action == 0x53 || isMilesAttacking())
	{
		_asm jmp loc_776D2A
	}
}

void ForceMiles(int player) {
	CurrentCharacter = Characters_Tails;
	LoadTails(0);
}


void Init_MilesActions() {
	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	MysticMelody_t = new Trampoline((int)0x6E76A0, (int)0x6E76A0 + 0x6, PlayMysticMelody);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x6d6911), CheckBreakIronBox);	
    WriteJump((void*)0x46EE00, sub_46EE00);

	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteData<1>((int*)0x776D20, 0x0);

	WriteCall((void*)0x43D6CD, ForceMiles);

	//WriteJump(reinterpret_cast<void*>(0x776d1e), CheckGravitySwitch);
	//WriteData<1>((int*)0x776d1e, )
}