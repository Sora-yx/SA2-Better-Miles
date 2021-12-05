#pragma once

void init_RankScore();
void CheckAndSetHackObject(CharObj2Base* co2);
void BoardSoundEffect(CharObj2Base* co2, EntityData1* data);


bool isRando();
bool isCharaSelect();
bool isSA1Tails();

FunctionPointer(void, Tails_runsAction, (EntityData1* data1, EntityData2* a2, CharObj2Base* a3, TailsCharObj2* a4), 0x74DC60);
signed int Tails_CheckActionWindowR(EntityData1* a1, EntityData2* a2, CharObj2Base* a3, TailsCharObj2* a4);

/*ObjectFunc(PrisonLaneDoor2, 0x605D50);
ObjectFunc(PrisonLaneDoor3, 0x608610);*/
ObjectFunc(PrisonLaneDoor4, 0x606A10);
FunctionPointer(int, njPushUnitMatrix_, (), 0x44B210);
int IsPlayerInsideSphere(NJS_VECTOR* position, float a2);
FunctionPointer(int, LoadShEffTex, (), 0x755DE0);


void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2);


FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff

FunctionPointer(int, AnimateMilesTails, (EntityData1* data1, CharObj2Base* a2, TailsCharObj2* a3), 0x751090);


bool Player_CheckBreakMaybe(int a1, EntityData1* a2, CharObj2Base* a3);
signed int CheckPlayerStop(EntityData1* a1, CharObj2Base* a2, EntityData2* a4);

FunctionPointer(void, DoGrindThing, (EntityData1* data, EntityData2* data2, CharObj2Base* co2, TailsCharObj2* co2Miles), 0x725F30);
FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2* a2, TailsCharObj2* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2* a2, TailsCharObj2* a3), 0x46D6D0);
FunctionPointer(int, calcGrindRotationMaybe, (NJS_VECTOR* v, Rotation* rot), 0x4905A0);
FunctionPointer(int, sub_447580, (NJS_OBJECT* v), 0x447580);
FunctionPointer(void, SetNewRot, (int a1, int a2, int a3), 0x46C490);
//FunctionPointer(signed int, sub_77FE10, (float* a1), 0x77FE10);
void sub_4273B0(NJS_VECTOR* a1, NJS_VECTOR* a2, float* a3);


DataPointer(float, FLOAT_01283704, 0x1283704);
DataArray(float, flt_25F02A0, 0x25F02A0, 5);

DataPointer(DWORD, dword_267053C, 0x267053C); //something checked for after image
void DoNextAction_r(int playerNum, char action, int unknown);


bool isMilesAttacking();
void Miles_DoCollisionAttackStuff(EntityData1* data1);
void DoNextAction_R(int playerNum, char action, int unknown);


VoidFunc(sub_47BB50, 0x47BB50);
void BetterMiles_Init();
void Init_NewAnimation();
void Init_MilesActions();
signed int __cdecl Miles_CheckNextActions_r(EntityData2* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);

static Buttons JumpButtons = Buttons_A;
static Buttons AttackButtons = Buttons_X;

void Init_VoicesFixes();


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
