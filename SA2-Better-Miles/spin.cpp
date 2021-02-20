#include "stdafx.h"


int FailSafeTimer = 0;
void Miles_CheckSpinAttack(TailsCharObj2* a1, EntityData1* a2, CharObj2Base* a3)
{

    if (!isCustomAnim || CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7 || a2->NextAction != 0)
        return;

    if (Controllers[a3->PlayerNum].on & (Buttons_X | Buttons_B) && (a2->Status & 0x2000) == 0)
    {
          //a2->NextAction = 39;
        a2->Action = 60;
        a3->AnimInfo.Next = Spin1;
        a3->AnimInfo.field_8 = 0;
        a1->field_1BC[418] |= 2u;
        FailSafeTimer = 0;
        PlaySoundProbably(8200, 0, 0, 0);

    }

    return;
}


//Field 10 or 14 = Frame
void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2)
{
    unsigned __int16 curAnim; // ax
    __int16 v4; // ax
    __int16 getCurAnim; // ax

    curAnim = a1->AnimInfo.Current;

    if (curAnim >= Spin1 && curAnim <= Spin10)
    {
        if (Controllers[a1->PlayerNum].on & (Buttons_X | Buttons_B))
        {
            if (CallGetAnalog(a2, a1, 0, 0))
            {
                //The animation of the spin attack changes depending on the player direction.
                v4 = (unsigned __int8)((((int)(4096
                    - (unsigned __int64)(atan2((double)(Controllers[a1->PlayerNum].y1 << 8),
                        (double)(Controllers[a1->PlayerNum].x1 << 8))
                        * 65536.0
                        * -0.1591549762031479)) >> 13) & 7)
                    + Spin3);

                if (a1->AnimInfo.field_10 >= 10.0) {
                    if (v4 == a1->AnimInfo.Current)
                    {
                        a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.field_10 & 1) + Spin1;
                    }
                    else
                    {
                        a1->AnimInfo.Next = v4;
                        Play3DSound_Pos(8200, &a2->Position, 0, 0, 0);
                    }
                }
            }
            else
            {
                getCurAnim = a1->AnimInfo.Current;

                if (a1->AnimInfo.field_10 >= 10.0) {
                    if (getCurAnim == Spin1 || getCurAnim == Spin2)
                    {
                        Play3DSound_Pos(8200, &a2->Position, 0, 0, 0);
                        a1->AnimInfo.Next = getCurAnim ^ 1;
                    }
                    else
                    {
                        a1->AnimInfo.Next = ((unsigned __int64)a1->AnimInfo.field_10 & 1) + Spin1;
                    }
                }
            }
        }
        else {
            if (++FailSafeTimer == 30) //FAILSAFE
            {
                a1->AnimInfo.Next = 0;
                a2->Action = 0;
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

void Init_MilesSpin() {
    WriteData<5>((void*)0x752567, 0x90); //Remove Tail Attack thing
    WriteData<3>((int*)0x751e56, 0x90);
    WriteData<11>((int*)0x74ed0a, 0x90);
}
