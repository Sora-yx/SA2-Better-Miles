#pragma once

enum TailsAnims : unsigned __int16 {
	Anm_Tails_RailL = 203,
	Anm_Tails_RailR,
	Anm_Tails_RailCrouchL,
	Anm_Tails_RailCrouchR,
	Anm_Tails_RailFastL,
	Anm_Tails_RailFastR,
	Anm_Tails_RailFastCL,
	Anm_Tails_RailFastCR,
	Anm_Tails_RailBalanceL,
	Anm_Tails_RailBalanceR,
	Anm_Tails_RailTrick1, // Awesome
	Anm_Tails_RailTrick2, // Cool
	Anm_Tails_RailTrick3 // Nice
};


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
	SpinningAir,
	TornadoStanding,
	TornadoMoving,
	TornadoAscending,
	TornadoDescending,
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


extern bool isInfiniteFly;
extern bool isLightDash;
extern bool isBounce;

void Init_MilesFly();
void Miles_ManageFly(taskwk* twp, motionwk2* mwp, playerwk* pwp, TailsCharObj2* tailsCO2);

void Miles_UnrollCheck(EntityData1* data1, EntityData2* data2, CharObj2Base* co2);
void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2);
DataPointer(WORD, word_170ACEE, 0x170ACEE);
void RollPhysicControlMain(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void Miles_PerformLightDash(CharObj2Base* co2, EntityData1* data);
void Init_MilesSpin();
void Miles_CheckSpinAttack(TailsCharObj2* a1, EntityData1* a2, CharObj2Base* a3, EntityData2* a4);
void spinOnFrames(playerwk* pwk, EntityData1* data1, TailsCharObj2* mCo2);
void spinLeaveGroundCheck(taskwk* twp, playerwk* pwp, TailsCharObj2* co2M);
void spinLandingCheck(taskwk* twp, playerwk* pwp);
void Miles_GetFloat(EntityData1* a1, CharObj2Base* a2);
bool CheckWaterSurface(CharObj2Base* a1, EntityData1* a2);

signed int Miles_SetNextActionSwim(TailsCharObj2* a1, EntityData1* a2);
void CheckFloatingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles);
void CheckSwimmingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles);
void CheckDivingStuff(EntityData2* data2, EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles);

signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2);

int setGrindingNextAction(TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);
void CheckGrindThing(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, TailsCharObj2* co2Miles);
void LoadRailParticules(TailsCharObj2* co2, EntityData2* data2);
void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2* a3);
void PlayGrindAnimation(EntityData1* data1, CharObj2Base* a3);

signed int Miles_PerformBounce(CharObj2Base* a1, EntityData1* a2);
signed int Miles_CheckBounceAttack(CharObj2Base* a1, EntityData1* a2);
void DoBounce(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2* data2);
void DoBounceOnFloor(EntityData1* data, CharObj2Base* co2, TailsCharObj2* co2Miles, EntityData2* data2);

signed int SetHandGranding(EntityData2* data2, CharObj2Base* co2, EntityData1* data1);
void DoHangGrinding(EntityData1* data, CharObj2Base* co2);
void CheckScoreTrick(EntityData1* data1, CharObj2Base* co2, EntityData2* data2, TailsCharObj2* MilesCO2);

void BoardStuff(EntityData2* data2, TailsCharObj2* co2Miles, EntityData1* data, CharObj2Base* co2);
void BoardJumpStuff(EntityData1* data, TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData2* data2);
float PhysicsBoardStuff2(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);
void BoardSparklesMaybe(EntityData2* a1, EntityData1* a2, TailsCharObj2* a3);
int PhysicsBoardStuff(CharObj2Base* a1, EntityData1* a2, EntityData2* a3, float a4);

void Check_LightDash(taskwk* twp, playerwk* pwp);
void CheckLightDashEnd(TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1);
void CheckRefreshLightDashTimer(CharObj2Base* co2, EntityData1* data, motionwk2* data2);
signed int __cdecl MilesCheckInput(EntityData2* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);

void Tornado_CallCheckInput(CharObj2Base* co2, EntityData1* data1);

void Tornado_RunsActions(EntityData2* data2, TailsCharObj2* co2Miles, EntityData1* data1, CharObj2Base* co2);
void Tornado_MainActions(EntityData1* data1, CharObj2Base* co2, EntityData2* data2);

void Cart_HackInit();
void Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
void LoadTailsExtra(char pnum);

void Delete_MilesAnim();
void RestoreNextAnim();
void resetMechWKPtr();

void resetLightdashTimer();