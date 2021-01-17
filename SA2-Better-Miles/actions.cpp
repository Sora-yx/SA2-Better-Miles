#include "stdafx.h"

Trampoline* CheckBreakObject_t;
Trampoline* BrokenDownSmokeExec_t;

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

void BrokenDownSmokeExec_r(ObjectMaster* obj) {

	if (CurrentCharacter != Characters_ChaoWalker && CurrentCharacter != Characters_DarkChaoWalker && CurrentCharacter != Characters_MechTails && CurrentCharacter != Characters_MechEggman) {
		ObjectFunc(origin, BrokenDownSmokeExec_t->Target());
		origin(obj);
	}
	else {
		DeleteObject(obj);
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
	//BrokenDownSmokeExec_t = new Trampoline((int)BrokenDownSmokeExec, (int)BrokenDownSmokeExec + 0x7, BrokenDownSmokeExec_r);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x6d6911), CheckBreakIronBox);	
    WriteJump((void*)0x46EE00, sub_46EE00);
}