#pragma once

void ReadConfig(const char* path);

extern HelperFunctions HelperFunctionsGlobal;
extern AnimationInfo TailsAnimationList_R[];
extern bool isCustomAnim;
extern bool isMechRemoved;
extern bool isMilesAdventure;
extern bool jumpVoice;
extern bool isCustomPhysics;
extern bool flySoundEffect;

void Init_StartEndPos();
void Init_VoicesFixes();
void BetterMiles_Init();
void Init_NewAnimation();
void Init_MilesActions();