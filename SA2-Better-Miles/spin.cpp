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
    if (Controllers[a3->PlayerNum].press & (Buttons_X | Buttons_B))
    {
        a2->Action = Spinning;
        a3->AnimInfo.Next = Spin1;
        a3->AnimInfo.field_8 = 0;
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

//Field 10 or 14 = Frame
void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2)
{
    unsigned __int16 curAnim; // ax
   // AnimationInfo* v3;
    __int16 v4; // ax
    __int16 v5; // ax
    __int16 getCurAnim; // ax

    curAnim = a1->AnimInfo.Current;

    if (curAnim == 94 || curAnim >= Spin1 && curAnim <= Spin10)
    {
        if ((double)a1->AnimInfo.field_10 >= 14.5) //Field10 should be the current frame of the anim. 
        {
            a1->AnimInfo.Next = 0; 
        }
        else if (Controllers[a1->PlayerNum].on & (Buttons_X | Buttons_B))
        {
            if (GetAnalogASM2(a2, a1, 0, 0))
            {
                //The animation of the spin attack changes depending on the player direction.
                v4 = (unsigned __int8)((((int)(4096
                    - (unsigned __int64)(atan2((double)(Controllers[a1->PlayerNum].y1 << 8),
                        (double)(Controllers[a1->PlayerNum].x1 << 8))
                        * 65536.0
                        * -0.1591549762031479)) >> 13) & 7)
                    + Spin3);

                if (a1->AnimInfo.field_10 >= 13.0) {
                    if (v4 == a1->AnimInfo.Current)
                    {
                        a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.field_10 & 1) + Spin1;
                    }
                    else
                    {
                        a1->AnimInfo.Next = v4;
                        //PlaySoundMiles(a2, 773);
                    }
                }
            }
            else
            {
                getCurAnim = a1->AnimInfo.Current;
                if (a1->AnimInfo.field_10 >= 12.0) {
                    if (getCurAnim == Spin1 || getCurAnim == Spin2)
                    {
                        a1->AnimInfo.Next = getCurAnim ^ 1;
                        //PlaySoundMiles(a2, 773);
                    }
                    else
                    {
                        a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.field_10 & 1) + Spin1;
                    }
                }
            }
        }
    }
}


void spinOnFrames(CharObj2Base* co2, EntityData1* data1) {
    if (co2->AnimInfo.Current) {
        Miles_SpinAttack(co2, data1);
    }
    else {
        data1->Action = 1;
        co2->AnimInfo.Current = 0;
    }
    return;
}

void Miles_SpinInit() {
    WriteData<5>((void*)0x752567, 0x90); //Remove Tail Attack thing
    WriteData<3>((int*)0x751e56, 0x90);
    WriteData<11>((int*)0x74ed0a, 0x90);
}
