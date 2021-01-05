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
extern bool isInfiniteFly;
void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2);
void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2);
void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3);
int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
signed int __declspec() GetAnalog(EntityData1* a1, CharObj2Base* a2, signed int* a3, int a4);

void Miles_SpinInit();

enum MilesState {
	Flying = 59,
	Spinning
};

enum MilesAnimation {
	FlyingAnim = 90,
	SpinningAnim = 94
};