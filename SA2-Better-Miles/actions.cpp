#include "stdafx.h"

Trampoline* CheckBreakObject_t;


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

void Init_MilesActions() {
	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x6d6911), CheckBreakIronBox);	
    WriteJump((void*)0x46EE00, sub_46EE00);
}