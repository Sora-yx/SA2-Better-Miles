#include "stdafx.h"

float savePosY = 0.0;

//signed int __usercall GetAnalog@<eax>(EntityData1 *data@<eax>, CharObj2Base *co2, signed int *angle, float* magnitude)
static const void* const GetAnalogPtr2 = (void*)0x45A870;
inline int GetAnalogASM2(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude)
{
    int result;
    __asm
    {
        push[magnitude]
        push[angle]
        push[co2]
        mov eax, [data]
        call GetAnalogPtr2
        mov result, eax
        add esp, 12
    }
    return result;
}



void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3)
{
    if (Controllers[a3->PlayerNum].on & (Buttons_X | Buttons_B))
    {
        a2->Action = Spinning;
        a3->AnimInfo.Current = Spin1;
        //a3->field_28 = Spin1;
        //a2->field_2 |= 2u;
        /*a1->SonicSpinTimeProbably = 0;
        a1->LightdashTime = 0;
        a1->field_12 = 0;
        a1->field_90.x = 0.0;
        a1->field_90.y = 0.0;
        a1->field_90.z = 0.0;*/
    }
}

static void __declspec(naked) CheckMiles_SpinAttackASM(NJS_OBJECT* a1, EntityData1* a2, CharObj2Base* a3)
{
    __asm
    {
        push ecx // a3
        push edx // a2
        push eax // a1

        // Call your __cdecl function here:
        call Miles_CheckSpinAttack

        pop eax // a1
        pop edx // a2
        pop ecx // a3
        retn
    }
}

void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2)
{
    unsigned __int16 curAnim; // ax
   // AnimationInfo* v3;
    __int16 v4; // ax
    __int16 v5; // ax
    __int16 v6; // ax

    curAnim = a1->AnimInfo.Current;

    if (curAnim == 94 || curAnim >= Spin1 && curAnim <= Spin10)
    {
        //v3 = &TailsAnimationList_R[curAnim];

        if ((double)a1->AnimInfo.Motion->nbFrame - 10.0  >= a1->AnimInfo.AnimationFrame) //IDK, hopefully it's correct. Back: Animation->motion->nbFrame - 10.0 >= a1->AnimationThing.Fra
        {
            //v3->NextAnimation = 0;
            a1->AnimInfo.Next = 0;
        }
        else if (Controllers[a1->PlayerNum].on & (Buttons_X | Buttons_B))
        {
            if (GetAnalogASM2(a2, a1, 0, 0)) 
            {
                v4 = (unsigned __int8)((((int)(4096
                    - (unsigned __int64)(atan2((double)(Controllers[a1->PlayerNum].y1 << 8),
                        (double)(Controllers[a1->PlayerNum].x1 << 8))
                        * 65536.0
                        * -0.1591549762031479)) >> 13) & 7)
                    + Spin3);
                if (v4 == a1->AnimInfo.Current)
                {
                    a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.AnimationFrame & 1) + Spin1;
                    //v3->NextAnimation = ((unsigned __int64)a1->AnimInfo.AnimationFrame & 1) + Spin1; //idk a1->AnimationThing.Frame & 1) + Spin2;
                }
                else
                {
                    a1->AnimInfo.Next = v4;
                    //v3->NextAnimation = v4;
                    //PlaySoundMiles(a2, 773);
                }
  
                /*if ((a2->Status & 3) != 0)
                {
                    savePosY = a2->Position.y;
                }
                else if (savePosY + 100.0 < a2->Position.y)
                {
                    a2->Action = Flying;
                    a1->AnimInfo.Current = FlyingAnim;
                   // a1->TailsFlightTime = 0.0;
                    /*v5 = a2->Status;
                    (a2->Object) &= 0xFEu;
                    a2->Status = v5 & 0xFEFF | 0x400;
                    BYTE2(a2->Object) |= 1u;
                    //PlaySoundMiles(a2, 1243);
                }*/
                
            }
            else
            {
                v6 = a1->AnimInfo.Current;
                if (v6 == Spin1 || v6 == Spin2)
                {
                    //v3->NextAnimation = v6 ^ 1;
                    a1->AnimInfo.Next = v6 ^ 1;
                    //PlaySoundMiles(a2, 773);
                }
                else
                {
                  //  v3->NextAnimation = ((unsigned __int64)a1->AnimInfo.AnimationFrame & 1) + Spin1; //idk
                    a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.AnimationFrame & 1) + Spin1;
                }
            }
        }
    }
}


void spinonFrames(CharObj2Base* co2, EntityData1* data1) {
    if (co2->AnimInfo.Current) {
        Miles_SpinAttack(co2, data1);
    }
    else {
        data1->Action = 0;
        co2->AnimInfo.Current = 0;
    }
    return;
}

void Miles_SpinInit() {
    WriteData<5>((void*)0x752567, 0x90);
    WriteData<3>((int*)0x751e56, 0x90);
    WriteData<11>((int*)0x74ed0a, 0x90);

    //WriteJump((void*)0x752D60, CheckMiles_SpinAttackASM);
    //Spin Attack stuff
/*WriteData<7>((int*)0x74ed0e, 0x90); //remove reset anim for spin attack
WriteData<4>((int*)0x74ed0a, 0x90); //remove reset action for spin attack.

WriteData<1>((int*)0xa0dbf2, 0x80); //Increase transition speed (from 0.125 to 1.0)
WriteData<1>((int*)0xa0dbf3, 0x3F);
WriteData<1>((int*)0xa0dbee, 0x5E);

WriteData<5>((void*)0x752d9a, 0x90); //Remove tails voice when doing spin attack;

//WriteData<1>((int*)0xa0dbf6, 0xC0);  //Animation Speed
//WriteData<1>((int*)0xa0dbf7, 0x3F);*/

}
