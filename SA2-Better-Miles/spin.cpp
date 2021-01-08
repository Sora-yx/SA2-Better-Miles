#include "stdafx.h"

float savePosY = 0.0;

/*void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2) {

	if ((a2->Status & (Status_Unknown1 | Status_Ground)) == 0)
		return;

	unsigned __int16 v2; // ax
	AnimationIndex v3; // ebp
	__int16 v4; // ax
	__int16 v5; // ax
	__int16 v6; // ax
	float getMilesPosY;

	if (a2->Action == Spinning) {
		if (Controllers[a1->PlayerNum].on & (Buttons_B | Buttons_X)) {
			a2->Status &= 0xDAFFu;
			PlaySoundProbably(8202, 0, 0, 0);
		}
		else {
			a1->AnimInfo.Next = 0;
			a2->Action = 0;
		}
	}
}*/



void Miles_CheckSpinAttack(EntityData1* a2, CharObj2Base* a3)
{
    if ((AttackButtons & Controllers[a3->PlayerNum].on) != 0)
    {
        a3->AnimInfo.Current = 118;
        //a3->AnimInfo.field_8 = 0;
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

void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2) //Loop system for animation might not need it for now.
{
    unsigned __int16 curAnim; // ax
    AnimationInfo* v3; // ebp

    __int16 v4; // ax
    __int16 v5; // ax
    __int16 v6; // ax

    curAnim = a1->AnimInfo.Current;
    //if (curAnim >= 43u && curAnim <= 53u) //in sadx, Miles spinning anim go from 43 to 53
    if (curAnim == SpinningAnim)
    {
        v3 = &TailsAnimList[curAnim];
        double frame = a1->AnimInfo.Motion->nbFrame;
       if (frame - 10.0 >= a1->AnimInfo.AnimationFrame)
        {
            v3->NextAnimation = 0;
        }
        else if ((AttackButtons & Controllers[a1->PlayerNum].on) != 0)
        {
            if (AnalogThings[a1->PlayerNum].magnitude != 0)
            {
                v4 = (unsigned __int8)((((int)(4096
                    - (unsigned __int64)(atan2(
                        (double)(Controllers[a1->PlayerNum].y1 << 8), //might be y2
                        (double)(Controllers[a1->PlayerNum].x1 << 8)) //might be x2
                        * 65536.0
                        * -0.1591549762031479)) >> 13) & 7)
                    + 46);
                if (v4 == a1->AnimInfo.Current)
                {
                    v3->NextAnimation = ((unsigned __int64)a1->AnimInfo.AnimationFrame & 1) + 44; //not sure about "animFrame"
                }
                else
                {
                    v3->NextAnimation = v4;
                    //PlaySoundMiles(a2, 773);
                }
       
                  if ((a2->Status & 3) != 0)
                  {
                      savePosY = a2->Position.y;
                  }
                  else if (savePosY + 100.0 < a2->Position.y)
                  {
                      a2->Action = Flying;
                      a1->AnimInfo.Current = FlyingAnim;
           
                      v5 = a2->Status;
                      //(a2->Object) &= 0xFEu;
                      a2->Status = v5 & 0xFEFF | 0x400;
                      //(a2->Object) |= 1u;
                      //PlaySoundMiles(a2, 1243);
                  }
                
            }
            else
            {
                v6 = a1->AnimInfo.Current;
                if (v6 == 44 || v6 == 45)
                {
                    v3->NextAnimation = v6 ^ 1;
                    //PlaySoundMiles(a2, 773);
                }
                else
                {
                    v3->NextAnimation = SpinningAnim; //((unsigned __int64)a1->AnimationThing.Frame & 1) +
                }
            }
        }
    }
}


void Miles_SpinInit() {
    WriteData<5>((void*)0x752567, 0x90);

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
