#pragma once

extern HelperFunctions HelperFunctionsGlobal;

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


struct CameraInfo2
{
	int field_0;
	int field_4;
	int field_8;
	char gapC[328];
	float field_154;
	float field_158;
	float field_15C;
	int field_160;
	char gap164[48];
	NJS_VECTOR position;
	Rotation rotation;
	char gap1AC[9000];
	int field_24D4;
};


DataPointer(CameraInfo2, CameraInfoPtr, 0x1DCFF40);


VoidFunc(sub_47BB50, 0x47BB50);

void BetterMiles_Init();

static const void* const Tails_FlyStartPtr = (void*)0x752DB0;
DataPointer(double, MilesFlySpeedValue, 0x9065a8);

static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;
extern bool isSA1Voice;
extern bool isInfiniteFly;
void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2);
void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2);
void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3);
int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
signed int __declspec() GetAnalog(EntityData1* a1, CharObj2Base* a2, signed int* a3, int a4);
void voices_Init();

void Miles_SpinInit();


enum MilesState {
	stand,
	walking,
	victory = 18,
	Flying = 59,
	Spinning,
	RealVictory = 120,
};

enum MilesAnimation {
	FlyingAnim = 90,
	SpinningAnim = 94,
	VictoryAnim = 118
};