#include "stdafx.h"

Trampoline* CheckBreakObject_t;

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

	if (isMilesAttacking())
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



void Init_MilesActions() {
	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
}