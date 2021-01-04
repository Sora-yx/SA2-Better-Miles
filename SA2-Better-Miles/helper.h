#pragma once

struct EntityData2_
{
	CharObj2Base* CharacterData;
	NJS_VECTOR VelocityDirection;
	NJS_VECTOR SomeCollisionVector;
	Rotation Forward;
	int field_28;
	int field_2C;
	int field_30;
	float field_34;
	float field_38;
	float SomeMultiplier;
};
DataArray(EntityData2_*, EntityData2Ptrs, 0x1DE95E0, 8);

void BetterMiles_Init();

static const void* const Tails_FlyStartPtr = (void*)0x752DB0;


static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;
extern bool isSA1Voice;
