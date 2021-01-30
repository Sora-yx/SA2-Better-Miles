#pragma once

extern bool isInfiniteFly;

signed int Tails_Jump(CharObj2Base* co2, EntityData1* data);

void Init_MilesFly();
int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2);
static const void* const Tails_FlyStartPtr = (void*)0x752DB0;
DataPointer(double, MilesFlySpeedValue, 0x9065a8);
void Miles_UnrollCheckSpeed(EntityData1* data1, CharObj2Base* co2);
DataPointer(WORD, word_170ACEE, 0x170ACEE);



void Init_MilesSpin();
void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3);
void spinOnFrames(CharObj2Base* co2, EntityData1* data1);


signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2);
void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2);

void setGrindingNextAction(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);
void CheckGrindThing(EntityData1* data1, EntityData2_* data2, CharObj2Base* co2, TailsCharObj2* co2Miles);
void LoadRailParticules(TailsCharObj2* co2, EntityData2_* data2);
void MoveCharacterOnRail(EntityData1* a1, CharObj2Base* a2, EntityData2_* a3);
void PlayGrindAnimation(EntityData1* data1, CharObj2Base* a3);

signed int SetHandGranding(EntityData2_* data2, CharObj2Base* co2, EntityData1* data1);
void DoHangGrinding(EntityData1* data, CharObj2Base* co2);
void CheckTrick(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2, TailsCharObj2* MilesCO2);

bool isSuperForm();