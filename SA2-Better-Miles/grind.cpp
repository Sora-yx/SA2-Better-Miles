#include "pch.h"

//Most of the functions here are directly copied pasted from the disassembly from Sonic grinding, with few extra fixes.
int setGrindingNextAction(TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) 
{

	int v8 = 0;
	signed int v37 = 0;
	int a2a = 0;
	int v20 = 0;
	Float v22 = 0.0;
	Float v23 = 0.0;
	Float v24 = 0.0;
	int v25 = 0;
	float v39 = 0.0;
	float v40 = 0.0;
	float v41 = 0.0;
	a4->Status = a4->Status & 0xFAFF | 0x2000;

	NJS_VECTOR result = { 1, 0, 0 };

	njUnitMatrix_();
	njRotateZ(0, v37);
	njRotateX(0, a2a);
	njRotateY(0, -a4->Rotation.y);

	njCalcVector(&result, &result, _nj_current_matrix_ptr_);
	v39 = fabs(a3->Speed.y);
	if (a3->Speed.x < 0.0f)
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
	a3->Speed.x = v23 + 1.0f;
	a4->Action = Grinding;

	if (isCustomAnim && (a3->CharID2 == Characters_Tails)) {
		if (njRandom() <= 0.5f) 
		{
			a3->AnimInfo.Next = Anm_Tails_RailFastL; //Anm_RailFastL;
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
	Play3DSound2(v25, &a4->Position, 0, 0, 127);
	VibeThing(0, 15, a3->PlayerNum, 6); //Vibe thing
	njPopMatrixEx();
	v8 = 1;
	a3->Speed.y = 0.0f;
	return 1;
}

void CheckGrindThing(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, TailsCharObj2* co2Miles) 
{
	if (MilesCheckInput(data2, co2Miles, co2, data1)) {
		return;
	}

	if ((data1->Status & Status_OnPath) == 0) {
		co2->AnimInfo.Next = 15;
		data1->Action = Action_Fall;
		co2->AnimInfo.Current = 15; //Falling
		data1->Status &= 0xDFFFu;
		return;
	}

	if (data1->Status & Status_DisableControl || !Jump_Pressed[co2->PlayerNum] || !sub_45B2C0(co2, co2->PlayerNum, data1) || sub_45B2C0(co2, co2->PlayerNum, data1) > 3) {

		if (TailsJump(co2, data1)) {
			data1->Status &= 0xDFFFu;
		}
		else if (co2->Speed.x > 0.8) {
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

			data2->Forward.y = data1->Rotation.y;
			if (co2->PhysData.RunSpeed > co2->Speed.x) {
				co2->Speed.x = co2->PhysData.RunSpeed;
			}

			data1->Action = Action_Fall;
			co2->AnimInfo.Current = 15;
			data1->Status &= 0xDFFFu;
		}

		return;
	}

	data1->Status &= 0xDFFFu;
	data1->Action = Action_Fall;
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

void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2* a3) {

	sub_46D040(a1, a2, a3);
	if (a1->Action != 72)
		getRailAccel(a2, a1, a3);
	return;
}

void PowderExecute_Rails(TailsCharObj2* sco2, NJS_VECTOR* dir) 
{
	float rng = static_cast<float>(rand()) * 0.00003f * 3.0f;
	if (rng > 0.0f) 
	{
		PowderExecute(dir, rng, (NJS_VECTOR*)&sco2->rightfoot_pos, sco2->base.PlayerNum);
	}

	rng = static_cast<float>(rand()) * 0.00003f * 3.0f;

	if (rng > 0.0f)
	{
		PowderExecute(dir, rng, (NJS_VECTOR*)&sco2->leftfoot_pos, sco2->base.PlayerNum);
	}
}

void LoadRailParticules(TailsCharObj2* co2, EntityData2* data2) {
	
	Float fabsSpd = fabs(co2->base.Speed.x);
	if (fabsSpd >= 3.7f) 
	{
		NJS_VECTOR speed;
		speed.x = data2->Velocity.x * 0.9f;
		speed.y = data2->Velocity.y * 0.9f;
		speed.z = data2->Velocity.z * 0.9f;

		PowderExecute_Rails(co2, &speed);
		sub_754EC0(co2->base.PlayerNum);
	}
}

void TailsRailAnim_ToNormal(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailCrouchL:
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		co2->AnimInfo.Next = Anm_Tails_RailL;
		break;
	case Anm_Tails_RailCrouchR:
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		co2->AnimInfo.Next = Anm_Tails_RailR;
		break;
	case Anm_Tails_RailFastCL:
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		co2->AnimInfo.Next = Anm_Tails_RailFastL;
		break;
	case Anm_Tails_RailFastCR:
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		co2->AnimInfo.Next = Anm_Tails_RailFastR;
		break;
	}
}

void TailsRailAnim_ToCrouch(CharObj2Base* co2) {
	switch (co2->AnimInfo.Current) {
	case Anm_Tails_RailL:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchL;
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		break;
	case Anm_Tails_RailR:
		co2->AnimInfo.Next = Anm_Tails_RailCrouchR;
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		break;
	case Anm_Tails_RailFastL:
		co2->AnimInfo.Next = Anm_Tails_RailFastCL;
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
		break;
	case Anm_Tails_RailFastR:
		co2->AnimInfo.Next = Anm_Tails_RailFastCR;
		co2->AnimInfo.field_18 = co2->AnimInfo.nframe;
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

//SA2 hardcode all the grinding animations id, sadly Miles already uses those for different actions, so we have to manually add new animation :(
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


void CheckScoreTrick(EntityData1* data1, CharObj2Base* co2, EntityData2* data2, TailsCharObj2* MilesCO2) {
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
	if (PlayerCheckBreak(idk, data1, co2) && co2->Speed.x > 0.0)
	{
		data1->Action = 12;
		idk2 = 18;
		idk3 = 0;
		co2->AnimInfo.Next = 18;
		co2->AnimInfo.field_8 = 0;
	}
	else
	{
		if (PlayerStop(data1, co2, data2))
		{
			data1->Rotation.x = data2->Forward.x;
			data1->Rotation.z = data2->Forward.z;
			if (njScalor((const NJS_VECTOR*)data2) >= (double)FLOAT_01283704)
			{
				if (njScalor((const NJS_VECTOR*)data2) >= 2.5)
				{
					co2->AnimInfo.Next = 17;
					VibeThing(0, 15, co2->PlayerNum, 6); //Vibe Thing
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
			data1->Rotation.x = data2->Forward.x;
			data1->Rotation.z = data2->Forward.z;
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

signed int SetHandGranding(EntityData2* data2, CharObj2Base* co2, EntityData1* data1) 
{
	NJS_VECTOR* vec = (NJS_VECTOR*)&co2->SomeVectors[4];

	data1->Status = data1->Status & 0xFAFF | Status_OnPath;

	NJS_VECTOR playerdir = { 1.0f, 0.0f, 0.0f };
	NJS_VECTOR playerup = { 0.0f, 1.0f, 0.0f };

	CalcVector_PlayerRot(data1, &playerdir);

	njPushMatrixEx();
	njRotateZ(0, data1->Rotation.z);
	njRotateX(0, data1->Rotation.x);
	njCalcPoint_(&playerup, &playerup, 0);
	njPopMatrixEx();

	data1->Rotation.x = (asin(-playerup.z) * 10430.38043493439);
	data1->Rotation.z = (atan2f(-playerup.y, -playerup.x) * -10430.38043493439);

	njPushMatrixEx();
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
	co2->Speed.x += 2.3f;
	co2->Speed.y = 0.0f;
	return 1;
}

void DoHangGrinding(EntityData1* data, CharObj2Base* co2) 
{
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
			if (co2->PhysData.RunSpeed > (double)co2->Speed.x)
			{
				co2->Speed.x = co2->PhysData.RunSpeed;
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