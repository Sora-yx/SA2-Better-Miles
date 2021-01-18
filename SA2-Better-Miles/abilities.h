#pragma once

extern bool isInfiniteFly;

signed int Tails_Jump(CharObj2Base* co2, EntityData1* data);

void MilesFly_Init();
int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
void MilesFly(EntityData1* data1, CharObj2Base* co2, EntityData2_* data2);
static const void* const Tails_FlyStartPtr = (void*)0x752DB0;
DataPointer(double, MilesFlySpeedValue, 0x9065a8);


void Miles_SpinInit();
void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3);
void spinOnFrames(CharObj2Base* co2, EntityData1* data1);


signed int Miles_RollCheckInput(EntityData1* a1, CharObj2Base* a2);
void Miles_UnrollCheckInput(EntityData1* data1, CharObj2Base* co2);

void setGrindingNextAction(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4);
void CheckGrindThing(EntityData1* data1, EntityData2_* data2, CharObj2Base* co2, TailsCharObj2* co2Miles);

