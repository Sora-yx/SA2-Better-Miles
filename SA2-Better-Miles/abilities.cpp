#include "stdafx.h"


void Tails_FlyMaybe(CharObj2Base* a1, EntityData1* a2)
{
    float v3; // edx
    float v4; // eax
    double v5; // st7
    int v6; // edx
    int v7; // eax
    double flyTime1 = 0.0; // st7
    double v9; // st7
    double v10; // st7
    char v11; // dl
    Sint8 v12; // al
    double v13; // st7
    double v14; // st7
    char v15; // cl
    char v16; // al
    float v17; // [esp+4h] [ebp-50h]
    NJS_VECTOR a1a; // [esp+8h] [ebp-4Ch] BYREF
    int v19 = 0; // [esp+14h] [ebp-40h]
    float v20 = 0.0; // [esp+24h] [ebp-30h]


    v3 = a2->Position.y;
    v4 = a2->Position.z;
    a1a.x = a2->Position.x;
    a1a.y = v3;
    a1a.z = v4;

    if (a2->Action != 59)
        return;

    if (v19 == 1)
    {
        v17 = a2->Position.y - v20;
        if (a1->Speed.y < -3.0 && v17 >= 25.0 && v17 < 50.0)
        {
            v5 = -3.0;
        LABEL_10:
            a1->idk4 = (v5 - a1->Speed.y) * 0.25 + a1->idk4;
            goto LABEL_11;
        }
        if (a1->Speed.y < -0.30000001 && v17 > 0.0 && v17 < 25.0)
        {
            v5 = -0.30000001;
            goto LABEL_10;
        }
    }
LABEL_11:
    v6 = a1->PlayerNum;
    a1->idk5 = 0;
    v7 = Controllers[v6].on;
    if ((v7 & Buttons_A) != 0)
    {
        //flyTime1 = a1->TailsFlightTime + 0.0083333338;
        if (flyTime1 > 1.0)
        {
            flyTime1 = 1.0;
        }
        //a1->TailsFlightTime = flyTime1;
        if (flyTime1 < 1.0)
        {
            a1->idk5 = 1;
            if (a1->Speed.y < 0.89999998)
            {
                v9 = a1->idk4 + 0.1;
LABEL_31:
                a1->idk4 = v9;
                goto LABEL_32;
            }
            v10 = 1.0 - a1->Speed.y;
LABEL_30:
            v9 = v10 + a1->idk4;
            goto LABEL_31;
        }
        if (a1->Speed.y >= 0.0)
        {
            goto LABEL_32;
        }
        if (a1->Speed.y > -2.6500001)
        {
            v9 = a1->idk4 - a1->Speed.y * 0.02;
            goto LABEL_31;
        }
        //a2->Action = 19;
        //a1->AnimationThing.Index = 42;
        v11 = a1->idk5;
        v12 = a1->PlayerNum;
        a2->Status &= 0xFBu;
        a1->idk5 = v11 & 0xFE;
        if (v12 != 1)
        {
            //PlaySound(1476, 0, 0, 0);
        }
    }
    else
    {
        if ((v7 & Buttons_B) == 0)
        {
            if (a1->Speed.y >= -2.0)
            {
                goto LABEL_32;
            }
            v10 = (-2.0 - a1->Speed.y) * 0.1;
            goto LABEL_30;
        }
        v13 = -a1->PhysData.VSpeedCap;
        if (v13 >= a1->Speed.y)
        {
            v14 = v13 - 0.1 - a1->Speed.y + a1->idk4;
        }
        else
        {
            v14 = a1->idk4 - 0.1;
        }
        a1->idk4 = v14;
        a1->idk5 = -1;
    }
LABEL_32:
    //PGetAccelerationFly(a2, a3, a1);
    v15 = 8;

    v16 = v15 + v15 * a1->idk5 / 2 + a1->idk5;
    a1->idk5 = v16;
    if (v16 >= 64)
    {
        a1->idk5 = 0;
    }
}


static int Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3) {

    a1->Action = 59;
    a1->Status &= 0xDAFFu;
    a2->AnimInfo.Animations->AnimNum = 90;
    a3->field_1BC[418] |= 1u;
    return PlayVoice(2, 1629);

}


int __declspec() Tails_FlyStartASM(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3)
{
    __asm
    {
        push ecx // a3
        push edx // a2
        push eax // a1

        // Call your __cdecl function here:
        call Tails_FlyStart

        add esp, 4 // a1<eax> is also used for return value
        pop edx // a2
        pop ecx // a3
        retn
    }
}


void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2) {


    unsigned __int16 v2; // ax
    AnimationIndex v3; // ebp
    __int16 v4; // ax
    __int16 v5; // ax
    __int16 v6; // ax
    float getMilesPosY;

    if (a2->Action == 60) {
        if (Controllers[a1->PlayerNum].on & (Buttons_B | Buttons_X)) {
            a2->Status &= 0xDAFFu;
            PlaySoundProbably(8202, 0, 0, 0);
        }
        else {
            a1->AnimInfo.Next = 1;
            a2->Action = 0;
        }
    }

}

void Miles_OnFrames() {
    if (!MainCharObj1[0] || GameState != GameStates_Ingame)
        return;

    Miles_SpinAttack(MainCharObj2[0], MainCharObj1[0]);
    Tails_FlyMaybe(MainCharObj2[0], MainCharObj1[0]);
}