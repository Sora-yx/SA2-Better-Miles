#include "pch.h"

ModelIndex* JumpBallMdl;

NJS_TEXNAME MilesBallTex[2];
NJS_TEXLIST MilesBall_Texlist = { arrayptrandlength(MilesBallTex) };

int spinTimer = 0;


void Miles_LoadJmpBall(TailsCharObj2* mco2) {
    JumpBallMdl = LoadMDLFile((char*)"jumpball.PRS"); //LoadMDLFile((char*)"SONICMDL.PRS");
    mco2->ModelList[jmpBallID].Index = JumpBallMdl[jmpBallID].Index;
    mco2->ModelList[jmpBallID].Model = JumpBallMdl[jmpBallID].Model;
    LoadTextureList("ballTex", &MilesBall_Texlist);
    return;
}

void __cdecl DoSpinDashRotationModel() {

    NJS_VECTOR spinDashThing = { 0.0f, -1.0f, 0.0f };

    njTranslateEx(&spinDashThing);
    NJS_MATRIX_PTR v14 = _nj_current_matrix_ptr_;
    njTranslate(_nj_current_matrix_ptr_, 0.0, 5.0, 0.0);
    njRotateZ(v14, 0x2000);
    njTranslate(v14, 0.0, -5.0, 0.0);
    spinDashThing.x = 0.69999999;
    spinDashThing.y = 1.1;
    spinDashThing.z = 0.80000001;
    njScaleEx(&spinDashThing);
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

        // Call your __cdecl function here:
        call DrawMiles_JumpBall

        pop ecx // mtn
        add esp, 4 // obj
        add esp, 4 // frame
        retn
    }
}

int Tails_JumpStart_r(CharObj2Base* co2, EntityData1* data)
{
    int v4; // edx
    ObjectMaster* dynColTask; // eax
    float* idk; // eax
    EntityData2* data2; // ecx
    int v9; // edx
    Float v10; // [esp+Ch] [ebp-8h]
    Float v11; // [esp+10h] [ebp-4h]

    if ((data->Status & Status_DisableControl) != 0 || !Jump_Pressed[co2->PlayerNum])
    {
        return 0;
    }

    data->Action = Action_Jump;
    dynColTask = co2->CurrentDyncolTask;
    co2->Speed.y = co2->PhysData.JumpSpeed;
    if (dynColTask)
    {
        idk = (float*)&dynColTask->UnknownA_ptr->field_0;
        if (idk)
        {
            data2 = MainCharData2[co2->PlayerNum];
            v10 = idk[5];
            v11 = idk[6];
            data2->Acceleration.x = idk[4];
            data2->Acceleration.y = v10;
            data2->Acceleration.z = v11;
        }
    }
    co2->AnimInfo.Next = 65;
    spinTimer = 0;
    data->Status &= Status_DisableControl | Status_OnPath | Status_DoNextAction | Status_HoldObject | Status_Attack | Status_LightDash | Status_Ball | Status_ObjectInteract | Status_Hurt | Status_Ground | 0x80F0;
    data->Status |= Status_Ball;
    co2->field_12 = 0;
    PlaySoundProbably(0x2000, 0, 0, 0);

    if (jumpVoice)
        PlayVoice(2, 1627);

    return 1;
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
    WriteJump((void*)0x751B80, Tails_JumpStartASM);
    return;
}