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
	co2->PhysData.Height = PhysicsArray[Characters_Tails].Height * 0.4000000059604645;
	co2->PhysData.Radius = PhysicsArray[Characters_Tails].Radius * 0.4000000059604645;
	co2->PhysData.FloorGrip = PhysicsArray[Characters_Tails].FloorGrip * 0.4000000059604645;
	co2->PhysData.CenterHeight = PhysicsArray[Characters_Tails].CenterHeight * 0.4000000059604645;
	v1->Collision->CollisionArray->push &= ~0x4000u;
	return;
}

void RollPhysicControlMain(EntityData1* a1, EntityData2* a2, CharObj2Base* a3) {
	PGetRotation(a1, a2, a3);
	SlowDownThing(a1, a2, a3);
	PlayerMoveStuff(a1, a2, a3);
}

signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2)
{
	if (CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7 || a1->NextAction != 0)
		return 0;

	if (Controllers[a2->PlayerNum].press & (Buttons_X | Buttons_B))
	{
		a2->Speed.x += 0.5;
		a1->Action = Rolling;
		a2->AnimInfo.Next = 12;
		a1->Status |= Status_Ball;
		SetPhysicRoll(a2, a1);
		return 1;
	}

	return 0;
}

signed int __fastcall ResetSpeedAction(EntityData1* a1, CharObj2Base* a2)
{
	if (a2->Speed.x > 0.0)
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
	double v2; // st7
	double v3; // st7
	float v5; // [esp+0h] [ebp-4h]
	float v6; // [esp+0h] [ebp-4h]
	float v7; // [esp+0h] [ebp-4h]

	v5 = a2->y * a1->y;
	v2 = v5;
	v6 = a2->x * a1->x;
	v3 = v2 + v6;
	v7 = a2->z * a1->z;
	return (float)(v3 + v7);
}
void ResetPlayerSpeed(CharObj2Base* result, EntityData2* a2)
{
	if (result)
	{
		result->Speed.z = 0.0;
		result->Speed.y = 0.0;
		result->Speed.x = 0.0;
	}
	if (a2)
	{
		a2->Velocity.z = 0.0;
		a2->Velocity.y = 0.0;
		a2->Velocity.x = 0.0;
	}
}

//Giant mess copied pasted from the disassembly, needed to manage the rolling thing.
int CheckGravityFallThing(EntityData1* a1, EntityData2* a3, CharObj2Base* a4)
{
	__int16 curStatus; // bx
	char curChar; // al
	int curaction; // cl
	char v8; // al
	NJS_VECTOR* v9; // esi
	int v10; // eax
	char v16; // [esp-4h] [ebp-18h]

	curStatus = a1->Status;
	if (((curStatus & (Status_OnObjectColli | Status_Ground)) != 0) ||
		(CurrentLevel == LevelIDs_CrazyGadget && (a1->Position.x >= -3750 && a1->Position.x <= -3500 || a1->Position.x >= -9400 && a1->Position.x <= -9160))) //hardcoded shit fix for CG somersault
	{
		return 0;
	}
	if (!ControllerEnabled[a4->PlayerNum]
		|| (a4->PreviousSurfaceFlags & SurfaceFlag_Dynamic) != 0
		|| (curaction = a1->Action, a1->Action != 1)
		|| a4->field_12
		|| sub_77FBA0(&Gravity, &a4->FloorNormal) >= -0.9847999811172485
		|| a4->PhysData.JogSpeed > (double)a4->Speed.x
		|| njScalor(&a4->WallNormal) != 0.0)
	{
		if ((curStatus & Status_Ball) != 0)
		{
			a1->Action = 6;
			return 1;
		}
		a1->Action = 10;
		a4->AnimInfo.Next = 15;
		return 1;
	}
	if ((Gravity.y >= -0.9999899864196777 || a1->Position.y - 60.0 < a4->SurfaceInfo.BottomSurface)
		&& (Gravity.y <= 0.9999899864196777 || a4->SurfaceInfo.TopSurface < a1->Position.y + 60.0))
	{
		a1->Action = 10;
		a4->AnimInfo.Next = 15;
		return 1;
	}
	a1->Action = 11;
	a4->AnimInfo.Next = 61;
	ResetPlayerSpeed(a4, a3);
	v16 = 2;
	v9 = &a1->Position;
	v10 = a4->CharID2;
	a4->IdleTime = 0;
	return 1;
}

void Miles_UnrollCheck(EntityData1* data1, EntityData2* data2, CharObj2Base* co2) {
	if (data1->NextAction == 0 || (data1->Status & Status_DoNextAction) == 0)
	{
		if (CheckGravityFallThing(data1, data2, co2)) {
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

			if (co2->PhysData.JogSpeed > (double)co2->Speed.x && ResetSpeedAction(data1, co2))
			{
				RestorePhysic(co2);
				data1->Status &= ~(Status_Attack | Status_Ball);
				return;
			}
		}
	}
	return;
}

void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2) {
	if ((Controllers[co2->PlayerNum].press & 0x402) != 0 || co2->Speed.x < 1.3)
	{
		RestorePhysic(co2);
		data1->Action = 1;
		co2->AnimInfo.Next = 26;
		data1->Status &= ~(Status_Attack | Status_Ball);
	}
}