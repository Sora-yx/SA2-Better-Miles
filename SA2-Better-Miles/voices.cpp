#include "stdafx.h"

static const void* const PlayWinnerVoicePtr = (void*)0x43ECA0;

void PlayWinnerVoicePtr_r(int pnum) {

    if (isSA1Voice)
    {
        PlayVoice(2, 5810);
        return;
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


void voices_Init() {
    WriteCall((void*)0x44f864, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x450816, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x451017, PlayWinnerVoiceProbablyASM);
    WriteCall((void*)0x4510af, PlayWinnerVoiceProbablyASM);


}