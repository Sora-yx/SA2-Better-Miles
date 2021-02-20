#include "stdafx.h"

//Most of the functions here are directly copied pasted from the disassembly from Sonic grinding, with few extra fixes.

static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static inline char PlaySound3DThingMaybe(int id, NJS_VECTOR* pos, int a3, char a4, char a5)
{
	char result;
	__asm
	{
		push[a5]
		push[a4]
		push[a3]
		mov esi, [pos]
		mov edi, [id]
		call Sub4372E0Ptr
		mov result, al
		add esp, 12
	}
	return result;
}

int setGrindingNextAction(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

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
	/*(a1[13].field_28) = 0;
	(a1[13].field_2C) = 0;*/
	result = { 1, 0, 0 };
	//sub_429710(); //Make the game crash sometimes not sure why
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
	a3->Speed.x = v23 + 1.0;
	a4->Action = Grinding;

	if (isCustomAnim) {
		if ((double)rand() * 0.000030517578125 <= 0.5) {
			a3->AnimInfo.Next = Anm_Tails_RailFastL;
		}
		else {
			a3->AnimInfo.Next = Anm_Tails_RailL;
		}
	}
	else {
		a3->AnimInfo.Next = 9;
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
	PlaySound3DThingMaybe(v25, &a4->Position, 0, 0, 127);
	CallVibeThing(0, 15, a3->PlayerNum, 6); //Vibe thing 
	sub_429000();
	v8 = 1;
	a3->Speed.y = 0.0;
	return 1;
}

static const void* const sub_45B2C0Ptr = (void*)0x45B2C0;
static inline int sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3)
{

	int result;

	__asm
	{
		mov esi, [a3]
		mov ecx, [a2]
		mov edx, [a1]

		call sub_45B2C0Ptr
		mov result, edx
	}

	return result;

}

static const void* const CheckGrindPtr = (void*)0x726D00;
static inline signed int CheckTrickASM(TailsCharObj2* a1, CharObj2Base* a2, EntityData1* a3)
{

	signed int result;

	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [a1]

		call CheckGrindPtr
		add esp, 8 // a2
		mov result, eax
	}
	return result;
}

void CheckGrindThing(EntityData1* data1, EntityData2_* data2, CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (data1->NextAction != 0 || data1->Status & Status_DoNextAction) {
		return;
	}

	if ((data1->Status & Status_OnPath) == 0) {
		co2->AnimInfo.Next = 15;
		data1->Action = 10; //SA2Action_LaunchJumpOrFalling
		co2->AnimInfo.Current = 15; //Falling
		data1->Status &= 0xDFFFu;
		return;
	}

	/*if (CheckTrickASM(co2Miles, co2, data1))
	{
		return;
	}*/

	if (data1->Status & Status_DisableControl || !Jump_Pressed[co2->PlayerNum] || !sub_45B2C0(co2, co2->PlayerNum, data1) || sub_45B2C0(co2, co2->PlayerNum, data1) > 3) {
		if (CheckTailsJump(co2, data1)) {
			data1->Status &= 0xDFFFu;
		}
		else if (*(WORD*)&co2Miles->field_1BC[420] <= 120) {
			if (!Action_Held[co2->PlayerNum])
			{
				co2->ActionWindowItems[co2->ActionWindowItemCount++ & 7] = 71;
			}
		}
		else {
			if (co2->AnimInfo.Current == Anm_Tails_RailBalanceL) {
				data1->Rotation.y -= 0x4000;
			}
			else if (co2->AnimInfo.Current == Anm_Tails_RailBalanceR) {
				data1->Rotation.y += 0x4000;
			}

			data2->Forward.x = data1->Rotation.y;
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

	Angle analog_angle;
	Float analog_mag;

	GetAnalog(data1, co2, &analog_angle, &analog_mag);

	analog_mag *= njSin((analog_angle - LOWORD(data1->Rotation.y)));

	if (analog_mag < 0) {
		data1->Rotation.y = data1->Rotation.y - (12288.0 - njScalor(&co2->Speed) * 800.0);
	}
	else {
		data1->Rotation.y = 12288.0 - njScalor(&co2->Speed) * 800.0 + data1->Rotation.y;
	}
}

//Math stuff that allow character to move on the rail
static const void* const sub_46D040Ptr = (void*)0x46D040;
static inline void sub_46D040(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3)
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
static inline void getRailAccel(CharObj2Base* a1, EntityData1* a2, EntityData2_* a3)
{

	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]

		// Call your __cdecl function here:
		call sub_46D140Ptr
		add esp, 8 // a2

	}
}

void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3) {
	sub_46D040(a1, a2, a3);
	if (a1->Action != 72)
		getRailAccel(a2, a1, a3);
	return;
}

//Sparkles Rail thing
//void __usercall sub_754EC0(int playernum@<ebx>)
static const void* const sub_754EC0Ptr = (void*)0x754EC0;
static inline void sub_754EC0(int playernum)
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

void TailsRailAnim_ToNormal(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailCrouchL:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_Tails_RailL;
		break;
	case Anm_Tails_RailCrouchR:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_Tails_RailR;
		break;
	case Anm_Tails_RailFastCL:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_Tails_RailFastL;
		break;
	case Anm_Tails_RailFastCR:
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		co2->AnimInfo.Next = Anm_Tails_RailFastR;
		break;
	}
}

void TailsRailAnim_ToCrouch(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailL:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchL;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_Tails_RailR:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchR;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_Tails_RailFastL:
		co2->AnimInfo.Next = Anm_Tails_RailFastCL;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	case Anm_Tails_RailFastR:
		co2->AnimInfo.Next = Anm_Tails_RailFastCR;
		co2->AnimInfo.field_18 = co2->AnimInfo.field_10;
		break;
	}
}

void TailsRailAnim_ToLeft(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailR:
	default:
		co2->AnimInfo.Next = Anm_Tails_RailL;
		break;
	case Anm_Tails_RailCrouchR:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchL;
		break;
	case Anm_Tails_RailFastR:
		co2->AnimInfo.Next = Anm_Tails_RailFastL;
		break;
	case Anm_Tails_RailFastCR:
		co2->AnimInfo.Next = Anm_Tails_RailFastCL;
		break;
	}
}

void TailsRailAnim_ToRight(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailL:
		co2->AnimInfo.Next = Anm_Tails_RailR;
		break;
	case Anm_Tails_RailCrouchL:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchR;
		break;
	case Anm_Tails_RailFastL:
		co2->AnimInfo.Next = Anm_Tails_RailFastR;
		break;
	case Anm_Tails_RailFastCL:
		co2->AnimInfo.Next = Anm_Tails_RailFastCR;
		break;
	}
}

//SA2 hardcode all the grinding animations id, sadly Miles already use those for different actions so we have to add new animation and full hack the function :(
void PlayGrindAnimation(EntityData1* data1, CharObj2Base* co2) {
	if (isCustomAnim == false || data1->Action != Grinding || co2->AnimInfo.Next == 15) {
		return;
	}
		
	if (Action_Held[co2->PlayerNum] == 0) {
		TailsRailAnim_ToNormal(co2);
	}
	else {
		TailsRailAnim_ToCrouch(co2);
	}

	Angle analog_angle;
	Float analog_mag;

	GetAnalog(data1, co2, &analog_angle, &analog_mag);

	analog_mag *= njSin((analog_angle - LOWORD(data1->Rotation.y)));

	if (analog_mag < 0) {
		TailsRailAnim_ToLeft(co2);
	}
	else {
		TailsRailAnim_ToRight(co2);
	}
}

static const void* const somethingAboutTrickPtr = (void*)0x45ABE0;
static inline bool somethingAboutTrick(int a1, EntityData1* a2, CharObj2Base* a3)
{
	int result;
	__asm
	{
		mov esi, [a3] // a3
		mov edi, [a2] // a2
		mov ecx, [a1] // a1

		// Call your __cdecl function here:
		call somethingAboutTrickPtr
		mov result, ecx
	}
	return result;
}

static const void* const somethingAboutTrick2Ptr = (void*)0x475100;
static inline signed int somethingAboutTrick2(EntityData1* a1, CharObj2Base* a2, EntityData2_* a4)
{
	
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a2] // a2
		mov eax, [a1] // a1

		// Call your __cdecl function here:
		call somethingAboutTrick2Ptr
		add esp, 8
		mov result, eax
	}
	return result;
}

static const void* const somethingAboutTrick3Ptr = (void*)0x474F80;
static inline int somethingAboutTrick3(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		// Call your __cdecl function here:
		call somethingAboutTrick3Ptr
		add esp, 4
		mov result, eax

	}
	return result;
}


static const void* const sub_4EC330Ptr = (void*)0x4EC330;
static inline void sub_4EC330(int a1, int a2, int a3)
{
	__asm
	{
		mov ecx, [a3] // a3
		mov ebx, [a2] // a2
		mov edx, [a1] // a1
		// Call your __cdecl function here:
		call sub_4EC330Ptr
	}
}


void CheckScoreTrick(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2, TailsCharObj2* MilesCO2) {

	char getcharID2 = 0;
	int curSound = 0;
	int idk = 0;
	int idk2 = 0;
	int idk3 = 0;
	char idk4 = 0;
	ObjectMaster* dispScore;
	ObjUnknownB* idk5;
	char idk6;

	if (data1->NextAction != 0 || !(data1->Status & Status_OnPath))
		return;

	getcharID2 = co2->CharID2;

	if (getcharID2 == 8)
	{
		curSound = 8214;
	}
	else
	{
		curSound = 8218;
		if (getcharID2 != 12)
		{
			curSound = 8195;
		}
	}
	PlaySoundProbably(curSound, 0, 0, 0);
	if (somethingAboutTrick(idk, data1, co2) && co2->Speed.x > 0.0)
	{
		data1->Action = 12;
		idk2 = 18;
		idk3 = 0;
		co2->AnimInfo.Next = 18;
		co2->AnimInfo.field_8 = 0;
	}
	else
	{

		if (somethingAboutTrick2(data1, co2, data2))
		{
			data1->Rotation.x = data2->field_28;
			data1->Rotation.z = data2->field_30;
			if (njScalor((const NJS_VECTOR*)data2) >= (double)FLOAT_01283704)
			{
				if (njScalor((const NJS_VECTOR*)data2) >= 2.5)
				{
					co2->AnimInfo.Next = 17;
					CallVibeThing(0, 15, co2->PlayerNum, 6); //Vibe Thing
				}
				else
				{
					co2->AnimInfo.Next = 16;
				}
				idk3 = 0;
				data1->Action = 0;
				co2->IdleTime = 0;
			}
			else
			{
				co2->AnimInfo.Next = 1;
				idk3 = 0;
				data1->Action = 0;
				co2->IdleTime = 0;
			}
		}
		else
		{
			data1->Rotation.x = data2->field_28;
			data1->Rotation.z = data2->field_30;
			data1->Action = 1;
			somethingAboutTrick3(co2, data1);
		}
	}
	sub_4EC330(idk3, co2->PlayerNum, idk2);

	idk6 = MilesCO2->field_3BC[1];
	if (!idk6)
	{
		DispTechniqueScore_Load(1000);
		return;
	}
	if (idk6 != 1)
	{
		//goto LABEL_241;
	}
	if (TwoPlayerMode)
	{
		return;
	}
	dispScore = AllocateObjectMaster(DispTechniqueScore_Main, 3, "DispTechniqueScore");
	if (!dispScore)
	{
		return;
	}
	idk5 = AllocateObjUnknownB();
	if (idk5)
	{
		//goto LABEL_240;
	}
	DeleteObject_(dispScore);
}


static const void* const sub_7274F0Ptr = (void*)0x7274F0;
float* sub_7274F0(EntityData1* a1)
{
	float* result;
	__asm
	{
		mov eax, [a1] // eax0
		// Call your __cdecl function here:
		call sub_7274F0Ptr
		fstp result
	}
	return result;
}


signed int SetHandGranding(EntityData2_* data2, CharObj2Base* co2, EntityData1* data1) {

	NJS_VECTOR* vec = (NJS_VECTOR*)&co2->field_144[4];

	data1->Status = data1->Status & 0xFAFF | Status_OnPath;

	NJS_VECTOR playerdir = { 1.0f, 0.0f, 0.0f };
	NJS_VECTOR playerup = { 0.0f, 1.0f, 0.0f };

	CalcVector_PlayerRot(data1, &playerdir);

	njPushUnitMatrix_();
	njRotateZ(0, data1->Rotation.z);
	njRotateX(0, data1->Rotation.x);
	njCalcPoint_(&playerup, &playerup, 0);
	njPopMatrixEx();

	data1->Rotation.x = (asin(-playerup.z) * 10430.38043493439);
	data1->Rotation.z = (atan2f(-playerup.y, -playerup.x) * -10430.38043493439);

	njPushUnitMatrix_();
	njRotateX(0, data1->Rotation.x);
	njRotateZ(0, data1->Rotation.z);
	njCalcPoint_(&playerdir, &playerup, 0);
	njPopMatrixEx();

	//data1->Rotation.y = (atan2f(playerup.x, playerup.z) * 10430.38043493439);
	data2->Forward.y = data1->Rotation.y;
	data1->Action = HandGrinding;
	if (isCustomAnim)
		co2->AnimInfo.Next = 200;
	else
		co2->AnimInfo.Next = 75;
	co2->Speed.x += 2.3;
	co2->Speed.y = 0.0f;
	return 1;
}

void DoHangGrinding(EntityData1* data, CharObj2Base* co2) {
	if (data->NextAction != 0)
		return;

		int curStatus = data->Status;
		int curChar2 = co2->CharID2;
		int curSound = 0;

		if ((curStatus & 0x2000) != 0)
		{
			if ((data->Status & 0x4000) == 0 && Jump_Pressed[co2->PlayerNum])
			{
				data->Action = 10;
				data->Status = curStatus & 0xDFFF;

				if (curChar2 == 8)
				{
					curSound = 8212;
				}
				else if (curChar2 == 12)
				{
					curSound = 8215;
				}
				else
				{
					curSound = 8193;
					if (co2->CharID)
					{
						curSound = 0x2000;
					}
				}
				PlaySoundProbably(curSound, 0, 0, 0);
				if (co2->PhysData.RollEnd > (double)co2->Speed.x)
				{
					co2->Speed.x = co2->PhysData.RollEnd;
				}
				co2->AnimInfo.Next = 15;
				co2->Speed.y = -1.5;
				sub_7274F0(data);
			}
		}
		else
		{
			data->Action = 10;
			co2->AnimInfo.Next = 15;
			data->Status &= 0xDFFFu;
			sub_7274F0(data);
		}
	
	return;
}