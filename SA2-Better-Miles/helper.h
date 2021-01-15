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
signed int CallGetAnalog(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude);
bool isMilesAttacking();

VoidFunc(sub_47BB50, 0x47BB50);
void BetterMiles_Init();
void Init_NewAnimation();
void Init_MilesActions();

static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;

void voices_Init();


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


