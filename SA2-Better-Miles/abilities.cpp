#include "stdafx.h"


void Miles_SpinAttack(CharObj2Base* a1, EntityData1* a2) {


    unsigned __int16 v2; // ax
    AnimationIndex v3; // ebp
    __int16 v4; // ax
    __int16 v5; // ax
    __int16 v6; // ax
    float getMilesPosY;

    if (a2->Action == 60) {
        if (Controllers[a1->PlayerNum].on & (Buttons_B | Buttons_X)) {

            if ((double)a1->AnimInfo.Current != 94)
            {
                a1->AnimInfo.Next = 94;
            }
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
}