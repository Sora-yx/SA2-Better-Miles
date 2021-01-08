#include "stdafx.h"

static const void* const PlayWinnerVoicePtr = (void*)0x43ECA0;
DataArray(int, TailsRankVoices, 0x173B7E4, 5);
DataPointer(char, CurrentLevelRank, 0x174B001);


void PlayWinnerVoicePtr_r(int pnum) {


    if (MainCharObj2[0]->CharID == Characters_Tails) {

        MainCharObj2[0]->CharID = Characters_Rouge; //give Tails a good camera
    }

    PlayWinnerVoiceProbably(pnum);
}


static void __declspec(naked) PlayWinnerVoiceProbablyASM(int pnum)
{
    __asm
    {
        push esi // pnum

        // Call your __cdecl function here:
        call PlayWinnerVoicePtr_r

        pop esi // pnum
        retn
    }
}


const void* const loc_44FD08 = (void*)0x44FD08;
__declspec(naked) void PlayRankVoice()
{
    __asm
    {
        push eax
        call PlayWinnerVoicePtr_r
        add esp, 4
        jmp loc_44FD08
    }
}




void voices_Init() {

    //WriteJump((void*)0x44FC5E, PlayRankVoice);

    WriteCall((void*)0x44f864, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x450816, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x451017, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x4510af, PlayWinnerVoiceProbablyASM);
}