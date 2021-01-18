#include "stdafx.h"


static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static void __declspec(naked) sub_4372E0(int a1, NJS_VECTOR* a2, int a3, char a4, char a5)
{
	__asm
	{
		push[esp + 0Ch] // a5
		push[esp + 0Ch] // a4
		push[esp + 0Ch] // a3
		push esi // a2
		push edi // a1

		// Call your __cdecl function here:
		call Sub4372E0Ptr

		pop edi // a1
		pop esi // a2
		add esp, 4 // a3
		add esp, 4 // a4
		add esp, 4 // a5
		retn
	}
}


void setGrindingNextAction(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

	NJS_VECTOR result;
	int v8 = 0;
	float* v21;
	signed int v37 = 0;
	int a2a = 0;
	int v20 = 0;
	double v22 = 0.0;
	double v23 = 0.0;
	double v24 = 0.0;
	int v25 = 0;
	float v39 = 0.0;
	float v40 = 0.0;
	float v41 = 0.0;

	a4->Status = a4->Status & 0xFAFF | 0x2000;
	(a1[13].field_28) = 0;
	(a1[13].field_2C) = 0;
	result = { 1, 0, 0 };
	sub_429710();
	v21 = nj_current_matrix_ptr_;
	if (nj_current_matrix_ptr_)
	{
		memset(nj_current_matrix_ptr_, v20, 0x30u);
		*v21 = 1.0;
		v21[5] = 1.0;
		v21[10] = 1.0;
	}
	if (v37)
	{
		njRotateZ(v21, v37);
	}
	if (a2a)
	{
		njRotateX(v21, a2a);
	}
	if (a4->Rotation.y)
	{
		njRotateY((float*)v21, -a4->Rotation.y);
	}
	njCalcPoint(&result, &result, v21);
	v39 = fabs(a3->Speed.y);
	if (a3->Speed.x < 0.0)
	{
		v24 = v39;
		v41 = fabs(result.y);
		v23 = a3->Speed.x - v24 * v41;
	}
	else
	{
		v22 = v39;
		v40 = fabs(result.y);
		v23 = v22 * v40 + a3->Speed.x;
	}
	a3->Speed.x = v23;
	a4->Action = 71;
	if ((double)rand() * 0.000030517578125 <= 0.5)
	{
		a3->AnimInfo.Next = 108;
	}
	else
	{
		a3->AnimInfo.Next = 104;
	}
	if (CurrentLevel == LevelIDs_GreenForest)
	{
		v25 = 6;
	}
	else
	{
		v25 = 2;
		if (CurrentLevel != LevelIDs_WhiteJungle)
		{
			v25 = 4103;
		}
	}
	sub_4372E0(v25, &a4->Position, 0, 0, 127);
	//sub_438E70(0, 15, a4->PlayerNum, 6); //Vibe thing 
	sub_429000();
	v8 = 1;
	a3->Speed.y = 0.0;
	return;
}


void idk(CharObj2Base* co2) {
	if (co2->PhysData.RollEnd > co2->Speed.x) {
		co2->Speed.x = co2->PhysData.RollEnd;
	}

	//v77 = __OFSUB__(HIWORD(co2->field_12), 12);
	//v76 = (HIWORD(co2->field_12) - 12) < 0;

	co2->Speed.y = 0.449999988079071 - njScalor(&co2->Speed) * 0.0260000005364418 + co2->Speed.y;

	/*if (v76 ^ v77) {
		HIWORD(co2->field_12) = 12;
	}*/

	co2->AnimInfo.Current = 15; // Falling
}


static const void* const sub_726D00Ptr = (void*)0x726D00;
static void __declspec(naked) DoTrickMaybe()
{
	__asm
	{
		push[esp + 04h] // a3
		push edi // a2
		push eax // a1

		// Call your __cdecl function here:
		call sub_726D00Ptr

		add esp, 4 // a1<eax> is also used for return value
		pop edi // a2
		add esp, 4 // a3
		retn
	}
}


static const void* const sub_45B2C0Ptr = (void*)0x45B2C0;
static signed int sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3)
{

	int result;
	__asm
	{
		push[a3]
		push[a2]
		push[a1]
		mov eax, [a1]
		call sub_45B2C0Ptr
		mov result, edx

		pop edx // a1
		pop ecx // a2
		pop esi // a3
	}
	return result;
}


void CheckGrindThing(EntityData1* data1, EntityData2_* data2, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (data1->NextAction != 0)
		return;

	if (!(data1->Status & Status_OnPath)) {
		data1->Action = 10; //SA2Action_LaunchJumpOrFalling
		co2->AnimInfo.Current = 15; //Falling
		data1->Status &= 0xDFFFu;
		return;
	}

	//if (CheckLaunchRailTrick(sonicco2, co2, data1)) {
		//return;
	//}

	if (data1->Status & Status_DisableControl || Jump_Pressed[co2->PlayerNum] == false || sub_45B2C0(co2, co2->PlayerNum, data1) == 0) {
		if (Tails_Jump(co2, data1)) {
			data1->Status &= 0xDFFFu;
		}
		else if (*(WORD*)&co2Miles->field_3BC[2] <= 120) {
			if (!Action_Held[co2->PlayerNum])
			{
				co2->ActionWindowItems[co2->ActionWindowItemCount++ & 7] = 71;
			}
		}
		else {
			if (co2->AnimInfo.Current == 112) { // anim rail lose balance left
				data1->Rotation.y -= 0x4000;
			}
			else if (co2->AnimInfo.Current == 113) {// anim rail lose balance right
				data1->Rotation.y += 0x4000;
			}

			data2->field_2C = data1->Rotation.y;
			if (co2->PhysData.RollEnd > co2->Speed.x) {
				co2->Speed.x = co2->PhysData.RollEnd;
			}
			data1->Action = 10; //SA2Action_LaunchJumpOrFalling
			co2->AnimInfo.Current = 15; //Falling
			data1->Status &= 0xDFFFu;
		}
		return;
	}

	data1->Status &= 0xDFFFu;
	data1->Action = 10; //SA2Action_LaunchJumpOrFalling
	PlaySoundProbably(8193, 0, 0, 0);

	Angle analog = 0;
	Angle analogdif = (analog - data1->Rotation.y);
	GetAnalog(data1, co2, (signed int*)&analog, 0);

	if (analogdif <= 0) {
		if (analogdif >= 0) {
			idk(co2);
			return;
		}

		data1->Rotation.y = data1->Rotation.y - (12288.0 - njScalor(&co2->Speed) * 800.0);
	}
	else {
		data1->Rotation.y = 12288.0 - njScalor(&co2->Speed) * 800.0 + data1->Rotation.y;
		idk(co2);
	}
}


//Math stuff that allow character to move on the rail
static const void* const sub_46D040Ptr = (void*)0x46D040;
int inline sub_46D040(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3)
{
	__asm
	{
		push[a3]
		mov ebx, [a2]
		mov eax, [a1]

		call sub_46D040Ptr

		add esp, 4 // a3        
	}
}

static const void* const sub_46D140Ptr = (void*)0x46D140;
int inline getRailAccel(CharObj2Base* a1, EntityData1* a2, EntityData2_* a3)
{
	int result;

	__asm
	{

		push[a3]
		push[a2]
		mov eax, [a1]

		// Call your __cdecl function here:
		call sub_46D140Ptr
		mov result, eax
		add esp, 8 // a2

	}
	return result;
}

void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3) {
	sub_46D040(a1, a2, a3);
	getRailAccel(a2, a1, a3);
	return;
}

//Sparkles Rail thing
//void __usercall sub_754EC0(int playernum@<ebx>)
static const void* const sub_754EC0Ptr = (void*)0x754EC0;
int inline sub_754EC0(int playernum)
{
	__asm {
		mov ebx, [playernum]
		call sub_754EC0Ptr
	}
}

void PowderExecute_Rails(TailsCharObj2* sco2, NJS_VECTOR* dir) {
	float idk = static_cast<float>(rand()) * 0.00003f * 3.0f;
	if (idk > 0.0f) {
		PowderExecute(dir, idk, (NJS_VECTOR*)&sco2->field_1BC[68], sco2->base.PlayerNum);
	}
}

void LoadRailParticules(TailsCharObj2* co2, EntityData2_* data2) {
	if (fabs(co2->base.Speed.x) >= 3.7f) {
		NJS_VECTOR speed;
		speed.x = data2->VelocityDirection.x * 0.9f;
		speed.y = data2->VelocityDirection.y * 0.9f;
		speed.z = data2->VelocityDirection.z * 0.9f;

		PowderExecute_Rails(co2, &speed);
		PowderExecute_Rails(co2, &speed);
		sub_754EC0(co2->base.PlayerNum);
	}
}

