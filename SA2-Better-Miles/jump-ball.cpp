#include "pch.h"

ModelIndex* JumpBallMdl;

NJS_TEXNAME MilesBallTex[2];
NJS_TEXLIST MilesBall_Texlist = { arrayptrandlength(MilesBallTex) };

int spinTimer = 0;

Trampoline* Tails_JumpStart_t;

void Miles_LoadJmpBall(TailsCharObj2* mco2) {
    JumpBallMdl = LoadMDLFile((char*)"\\Models\\jumpball.PRS"); 
    mco2->ModelList[jmpBallID].Index = JumpBallMdl[jmpBallID].Index;
    mco2->ModelList[jmpBallID].Model = JumpBallMdl[jmpBallID].Model;
    LoadTextureList("ballTex", &MilesBall_Texlist);
    return;
}

void DrawMiles_JumpBall(NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) {

    char pID = MilesCO2Extern->base.PlayerNum;
    EntityData1* data1 = MainCharObj1[pID];
    TailsCharObj2* mCO2 = MilesCO2Extern;
    NJS_VECTOR scale = { 0.9f, 0.9f, 0.9f };

    if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0)
    {
        mdl = CharacterModels[mCO2->base.AnimInfo.Animations[30].ModelNum].Model;// ball form
        njSetTexture(&MilesBall_Texlist);
        njScaleV_(&scale);
        motion = CharacterAnimations[mCO2->base.AnimInfo.Animations[mCO2->base.AnimInfo.Animations[30].AnimNum].AnimNum].Animation;
    }

    return DrawMotionAndObject(motion, mdl, frame);
}

static void __declspec(naked) DrawMotionAndObject_Hack()
{
    __asm
    {
        push[esp + 08h] // frame
        push[esp + 08h] // obj
        push ecx // mtn

        call DrawMiles_JumpBall

        pop ecx // mtn
        add esp, 4 // obj
        add esp, 4 // frame
        retn
    }
}

static inline signed int Tails_JumpStart_Origin(CharObj2Base* co2, EntityData1* data)
{
    const auto target = Tails_JumpStart_t->Target();
    signed int result;

    __asm
    {
        mov ecx, [data]
        mov eax, [co2]
        call target
        mov result, eax
    }

    return result;
}


int Tails_JumpStart_r(CharObj2Base* co2, EntityData1* data)
{
    signed int result = Tails_JumpStart_Origin(co2, data);

    if (result == 1 && data->Action == Action_Jump)
    {
        data->Status |= Status_Ball;
    }
      
    return result;
}

static void __declspec(naked) Tails_JumpStartASM()
{
    __asm
    {
        push ecx // data
        push eax // co2

        // Call your __cdecl function here:
        call Tails_JumpStart_r

        add esp, 4 // co2<eax> is also used for return value
        pop ecx // data
        retn
    }
}


void Init_JumpBallhack() {

    if (!isJumpBall)
        return;

    WriteCall((void*)0x750ABF, DrawMotionAndObject_Hack);

    Tails_JumpStart_t = new Trampoline((int)0x751B80, (int)0x751B85, Tails_JumpStartASM);
    return;
}