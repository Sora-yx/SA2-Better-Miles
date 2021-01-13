#pragma once

extern HelperFunctions HelperFunctionsGlobal;
extern AnimationInfo TailsAnimationList_R[];
extern bool isCustomAnim;

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

FunctionPointer(void, sub_45B610, (EntityData1* data, EntityData2_* a3, CharObj2Base* data2), 0x45B610);
DataArray(EntityData2_*, EntityData2Ptrs, 0x1DE95E0, 8);
DataPointer(char, TimerStopped, 0x174afda);

void spinOnFrames(CharObj2Base* co2, EntityData1* data1);

VoidFunc(sub_47BB50, 0x47BB50);
void MilesFly_Init();
void BetterMiles_Init();

static const void* const Tails_FlyStartPtr = (void*)0x752DB0;
DataPointer(double, MilesFlySpeedValue, 0x9065a8);

static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;
extern bool isSA1Voice;
extern bool isInfiniteFly;
void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2);
void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3);
int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2);
void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2);

void voices_Init();

void Miles_SpinInit();


enum MilesState {
	Standing,
	Running,
	Jumping = 6,
	ObjectControl = 18,
	Pulley = 51,
	Flying = 59,
	Spinning,
	VictoryPose = 190,
	Rolling
};



enum MilesAnimation {
	FlyingAnim = 90,
	TailAttackAnim = 94,
	VictoryAnim = 118,
	VictoryPoseEnd,
	Spin1,
	Spin2,
	Spin3,
	Spin4,
	Spin5,
	Spin6,
	Spin7,
	Spin8,
	Spin9,
	Spin10,
	RollAnim
};


