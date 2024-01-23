#pragma once

void ReadConfig(const char* path);
#define TaskHook static FunctionHook<void, ObjectMaster*>

extern HMODULE SA2Anim;
extern HMODULE SA1Char;

extern HelperFunctions HelperFunctionsGlobal;
extern AnimationInfo TailsAnimationList_R[];
extern bool isCustomAnim;
extern bool isMechRemoved;
extern bool isMilesAdventure;
extern bool jumpVoice;
extern bool isCustomPhysics;
extern bool flySoundEffect;
extern bool isJumpBall;
extern bool tornadoMusic;
extern bool tornadoConfig;
extern uint8_t sfxVol;
extern uint8_t voiceVol;
extern Buttons RollBtn;
extern Buttons BounceBtn;
extern Buttons SpinBtn;
extern Buttons LightDashBtn;

const int jmpBallID = 230;

void Init_StartEndPos();
void Init_VoicesFixes();
void BetterMiles_Init();
void Init_NewAnimation();
void Init_ObjectsHacks();
void Init_JumpBallhack();
extern int spinTimer;

#define TARGET_DYNAMIC(name) ((decltype(name##_r)*)name##_t->Target()) //sf94