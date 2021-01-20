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

FunctionPointer(int, njPushUnitMatrix_, (), 0x44B210);
FunctionPointer(void, sub_45B610, (EntityData1* data, EntityData2_* a3, CharObj2Base* data2), 0x45B610);
FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff
DataPointer(NJS_MATRIX_PTR, nj_current_matrix_ptr_, 0x1A557FC);


FunctionPointer(void, DoGrindThing, (EntityData1* data, EntityData2_* data2, CharObj2Base* co2, TailsCharObj2* co2Miles), 0x725F30);
FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2_* a2, TailsCharObj2* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2_* a2, TailsCharObj2* a3), 0x46D6D0);
FunctionPointer(int, calcHandGrindRotationMaybe, (NJS_VECTOR* v, Rotation* rot), 0x4905A0);

signed int SetHandGranding(EntityData2_* data2, TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1);

DataArray(EntityData2_*, EntityData2Ptrs, 0x1DE95E0, 8);
DataPointer(char, TimerStopped, 0x174afda);
DataPointer(float, FLOAT_01283704, 0x1283704);
signed int CallGetAnalog(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude);
bool isMilesAttacking();
void Miles_DoCollisionAttackStuff(EntityData1* data1);

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
	Grinding = 71,
	HandGrinding,
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


