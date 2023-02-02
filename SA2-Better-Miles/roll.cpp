#include "pch.h"

//Restore Miles Physic
void RestorePhysic(CharObj2Base* co2) {
	co2->PhysData.Height = PhysicsArray[Characters_Tails].Height;
	co2->PhysData.Radius = PhysicsArray[Characters_Tails].Radius;
	co2->PhysData.FloorGrip = PhysicsArray[Characters_Tails].FloorGrip;
	co2->PhysData.CenterHeight = PhysicsArray[Characters_Tails].CenterHeight;
	return;
}

//Apply Somersault physic/collision 
void SetPhysicRoll(CharObj2Base* co2, EntityData1* v1) {
	co2->PhysData.Height = PhysicsArray[Characters_Tails].Height * 0.4000000059604645f;
	co2->PhysData.Radius = PhysicsArray[Characters_Tails].Radius * 0.4000000059604645f;
	co2->PhysData.FloorGrip = PhysicsArray[Characters_Tails].FloorGrip * 0.4000000059604645f;
	co2->PhysData.CenterHeight = PhysicsArray[Characters_Tails].CenterHeight * 0.4000000059604645f;
	v1->Collision->CollisionArray->push &= ~0x4000u;
	return;
}

void RollPhysicControlMain(EntityData1* a1, EntityData2* a2, CharObj2Base* a3) {
	PGetRotation(a1, a2, a3);
	PGetInertia(a1, a2, a3);
	PlayerMoveStuff(a1, a2, a3);
}

signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2)
{
	if (CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7 || a1->NextAction != 0)
		return 0;

	if (Controllers[a2->PlayerNum].press & RollBtn)
	{
		a2->Speed.x += 0.5f;
		a1->Action = Rolling;
		a2->AnimInfo.Next = 12;
		a1->Status |= Status_Ball | Status_Attack;
		SetPhysicRoll(a2, a1);
		return 1;
	}

	return 0;
}

signed int ResetSpeedAction(EntityData1* a1, CharObj2Base* a2)
{
	if (a2->Speed.x > 0.0f)
	{
		a1->Action = 1;
	}
	else
	{
		a1->Action = 0;
		a2->IdleTime = 0;
	}
	a2->AnimInfo.Next = 26;
	a1->Status &= 0xFAFFu;
	return 1;
}

double sub_77FBA0(NJS_VECTOR* a1, NJS_VECTOR* a2)
{
	double v2;
	double v3;
	float v5;
	float v6;
	float v7;

	v5 = a2->y * a1->y;
	v2 = v5;
	v6 = a2->x * a1->x;
	v3 = v2 + v6;
	v7 = a2->z * a1->z;
	return (float)(v3 + v7);
}
void ResetPlayerSpeed(CharObj2Base* pwp, EntityData2* mwp)
{
	if (pwp)
	{
		pwp->Speed = { 0.0f };

	}

	if (mwp)
	{
		mwp->Velocity = { 0.0f };
	}
}

//Giant mess copied pasted from the disassembly, needed to manage the rolling thing.
int CheckGravityFallThing(EntityData1* twp, EntityData2* a3, CharObj2Base* pwp)
{
	int v10;
	char v16;

	__int16 curStatus = twp->Status;
	if (((curStatus & (Status_OnObjectColli | Status_Ground)) != 0) ||
		(CurrentLevel == LevelIDs_CrazyGadget && (twp->Position.x >= -3750 && twp->Position.x <= -3500 || twp->Position.x >= -9400 && twp->Position.x <= -9160))) //hardcoded shit fix for CG somersault
	{
		return 0;
	}

	if (!ControllerEnabled[pwp->PlayerNum]
		|| (pwp->PreviousSurfaceFlags & SurfaceFlag_Dynamic) != 0 || (twp->Action != 1) || pwp->field_12
		|| sub_77FBA0(&Gravity, &pwp->FloorNormal) >= -0.9847999811172485f || pwp->PhysData.JogSpeed > pwp->Speed.x
		|| njScalor(&pwp->WallNormal) != 0.0f)
	{
		if ((curStatus & Status_Ball) != 0)
		{
			twp->Action = 6;
			return 1;
		}
		twp->Action = 10;
		pwp->AnimInfo.Next = 15;
		return 1;
	}
	if ((Gravity.y >= -0.9999899864196777f || twp->Position.y - 60.0f < pwp->SurfaceInfo.BottomSurface)
		&& (Gravity.y <= 0.9999899864196777f || pwp->SurfaceInfo.TopSurface < twp->Position.y + 60.0f))
	{
		twp->Action = 10;
		pwp->AnimInfo.Next = 15;
		return 1;
	}
	twp->Action = 11;
	pwp->AnimInfo.Next = 61;
	ResetPlayerSpeed(pwp, a3);
	v16 = 2;
	v10 = pwp->CharID2;
	pwp->IdleTime = 0;
	return 1;
}

void Miles_UnrollCheck(EntityData1* data1, EntityData2* data2, CharObj2Base* co2) {

	if (CheckGravityFallThing(data1, data2, co2)) 
	{
		RestorePhysic(co2);
		co2->AnimInfo.Next = 66;
		data1->Status = data1->Status & 0xDFFF | 0x500;
	}
	else
	{
		if (TailsJump(co2, data1))
		{
			RestorePhysic(co2);
			data1->Status &= ~Status_Ball;
			return;
		}

		if (co2->PhysData.JogSpeed > co2->Speed.x && ResetSpeedAction(data1, co2))
		{
			RestorePhysic(co2);
			data1->Status &= ~(Status_Attack | Status_Ball);
			return;
		}
	}

}

void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2) {

	if ((Controllers[co2->PlayerNum].press & RollBtn) != 0 || co2->Speed.x < 1.3f)
	{
		RestorePhysic(co2);
		data1->Action = Running;
		co2->AnimInfo.Next = 26;
		data1->Status &= ~(Status_Attack | Status_Ball);
	}
}