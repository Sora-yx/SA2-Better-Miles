#pragma once

extern HelperFunctions HelperFunctionsGlobal;
extern AnimationInfo TailsAnimationList_R[];
extern bool isCustomAnim;
extern bool isMechRemoved;
extern bool isMilesAdventure;
extern bool jumpVoice;
extern bool isCustomPhysics;

void init_RankScore();
void CheckAndSetHackObjectMiles();

union taskwork_subs
{
	char b[4];
	__int16 w[2];
	int l;
	float f;
	void* ptr;
};

#pragma pack(push, 1)
struct EntityData2_R
{
	NJS_POINT3 spd;
	NJS_POINT3 acc;
	Rotation ang_aim;
	Rotation ang_spd;
	float force;
	float accel;
	float frict;
};
#pragma pack(pop)

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

struct CollisionInfo_
{
	__int16 char0;
	__int16 field_2;
	uint16_t word4;
	uint16_t Count;
	float field_8;
	CollisionData* CollisionArray;
	uint8_t f10[140];
	ObjectMaster* Object;
	__int16 field_A0;
	__int16 field_A2;
	CollisionInfo* CollidingObject;
};

#pragma pack(push, 1)
struct __declspec(align(2)) HomingAttackTarget
{
	EntityData1* entity;
	float distance;
};
#pragma pack(pop)

void FixAnimationFinalBossOnFrames(CharObj2Base* co2, EntityData1* data1);
bool isRando();
bool isCharaSelect();

FunctionPointer(void, Tails_runsAction, (EntityData1* data1, EntityData2_R* a2, CharObj2Base* a3, TailsCharObj2* a4), 0x74DC60);
signed int Tails_CheckActionWindowR(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3, TailsCharObj2* a4);
ObjectFunc(Dynamite_Main, 0x6da880);
ObjectFunc(DynamiteHiddenBase_Main, 0x714610);
ObjectFunc(DynamiteSandOcean_Main, 0x65AEA0);
ObjectFunc(PrisonLaneDoor, 0x606400);
/*ObjectFunc(PrisonLaneDoor2, 0x605D50);
ObjectFunc(PrisonLaneDoor3, 0x608610);*/
ObjectFunc(PrisonLaneDoor4, 0x606A10);
FunctionPointer(int, njPushUnitMatrix_, (), 0x44B210);
int IsPlayerInsideSphere(NJS_VECTOR* position, float a2);
FunctionPointer(int, LoadShEffTex, (), 0x755DE0);

//control/physic functions
FunctionPointer(void, sub_45B610, (EntityData1* data, EntityData2_R* a3, CharObj2Base* co2), 0x45B610);
void PlayerMoveStuff(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);
FunctionPointer(void, sub_474990, (EntityData1* data, EntityData2_R* a3, CharObj2Base* co2), 0x474990);
FunctionPointer(void, PlayerGetRotation, (EntityData1* data, EntityData2_R* a3, CharObj2Base* co2), 0x45FA70);
void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2);
float SlowDownThing_r(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);

//Roll functions
int CallPlayerCheckFallGravityStuff(EntityData1* a1, int a2, EntityData2_R* a3, CharObj2Base* a4);

void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2);
void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2);

FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff
DataPointer(NJS_MATRIX_PTR, nj_current_matrix_ptr_, 0x1A557FC);
void CallVibeThing(int a1, signed int a2, int a3, signed int a4);
FunctionPointer(int, AnimateMilesTails, (EntityData1* data1, CharObj2Base* a2, TailsCharObj2* a3), 0x751090);

void CheckLightDashEnd(TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1);

void CheckRefreshLightDashTimer(CharObj2Base* co2, EntityData1* data);
void InitLightDashStuff();

void PlayerResetPosition(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);
bool Player_CheckBreakMaybe(int a1, EntityData1* a2, CharObj2Base* a3);
signed int CheckPlayerStop(EntityData1* a1, CharObj2Base* a2, EntityData2_R* a4);

FunctionPointer(void, DoGrindThing, (EntityData1* data, EntityData2_R* data2, CharObj2Base* co2, TailsCharObj2* co2Miles), 0x725F30);
FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2_R* a2, TailsCharObj2* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2_R* a2, TailsCharObj2* a3), 0x46D6D0);
FunctionPointer(int, calcGrindRotationMaybe, (NJS_VECTOR* v, Rotation* rot), 0x4905A0);
FunctionPointer(int, sub_447580, (NJS_OBJECT* v), 0x447580);
FunctionPointer(EntityData1*, sub_46C490, (int a1, int a2, int a3), 0x46C490);
//FunctionPointer(signed int, sub_77FE10, (float* a1), 0x77FE10);
void sub_4273B0(NJS_VECTOR* a1, NJS_VECTOR* a2, float* a3);
FunctionPointer(void, PlayerAfterImageMaybe, (NJS_OBJECT* a1, int a2, NJS_TEXLIST* a3, float a4, char a5), 0x476C20);

DataArray(EntityData2_R*, EntityData2Ptrs, 0x1DE95E0, 8);
DataPointer(char, TimerStopped, 0x174afda);
DataPointer(float, FLOAT_01283704, 0x1283704);
DataArray(float, flt_25F02A0, 0x25F02A0, 5);

DataPointer(DWORD, dword_267053C, 0x267053C); //something checked for after image
void DoNextAction_r(int playerNum, char action, int unknown);

void CheckAndDisplayAfterImage(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
signed int CallGetAnalog(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude);
bool isMilesAttacking();
void Miles_DoCollisionAttackStuff(EntityData1* data1);
int Call_sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3);
int PlayerSetPosition(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3);
void DoNextAction_R(int playerNum, char action, int unknown);
char Play3DSoundPosThing(int id, NJS_VECTOR* pos, int a3, char a4, char a5);

VoidFunc(sub_47BB50, 0x47BB50);
void BetterMiles_Init();
void Init_NewAnimation();
void Init_MilesActions();
signed int __cdecl Miles_CheckNextActions_r(EntityData2_R* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);

static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;

void Init_VoicesFixes();
DataArray(int, SonicRankVoices, 0x173B7D0, 5);
DataArray(int, TailsRankVoices, 0x173B7E4, 5);
DataArray(int, KnucklesRankVoices, 0x173B7F8, 5);
DataArray(int, EggmanRankVoices, 0x173B80C, 5);
DataArray(int, ShadowRankVoices, 0x173B820, 5);
DataArray(int, RougeRankVoices, 0x173B834, 5);
DataPointer(char, CurrentLevelRank, 0x174B001);

ObjectFunc(RocketIG, 0x6A10A0);
ObjectFunc(DoorIG, 0x69D1D0);
ObjectFunc(DoorIG2, 0x69F460);
ObjectFunc(DoorCCThing, 0x79AFB0);
ObjectFunc(DoorHB, 0x715560);
ObjectFunc(MetalBox, 0x6D6490);
ObjectFunc(MetalBoxGravity, 0x77BB90);
ObjectFunc(CGTubeGlass, 0x776060);

enum MilesState {
	Standing,
	Running,
	Jumping = 6,
	ObjectControl = 18,
	MysticMelody = 45,
	Pulley = 51,
	Flying = 59,
	Spinning,
	Bounce = 69,
	BounceFloor,
	Grinding = 71,
	HandGrinding,
	Rolling = 90,
	LightDash,
	FloatingOnWater,
	Swimming,
	Diving,
	VictoryPose = 190,
};

enum MilesAnimation {
	FlyingAnim = 90,
	TailAttackAnim = 94,
	SwapAnim = 216,
	VictorySuperForm,
	LightdashAnim,
	PaddingAnim,
	BeginDivingAnim,
	DivingAnim,
	BegingSurfacingAnim,
	SurfacingAnim,
	FloatingWaterAnim,
	VictoryAnim,
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
};
