#include "stdafx.h"

static const void* const PlayWinnerVoicePtr = (void*)0x43ECA0;
DataArray(int, TailsRankVoices, 0x173B7E4, 5);
DataPointer(char, CurrentLevelRank, 0x174B001);

char realChar = 0;
void FixCamEndPos(int num) {

    if (CurrentLevel == LevelIDs_Route101280)
        return;

    realChar = MainCharObj2[0]->CharID;

   if (MainCharObj2[0]->CharID == Characters_Tails) {
       MainCharObj2[0]->CharID = Characters_Rouge; //Trick the game to make it think we are playing Rouge so it give a good camera for victory pose.
    }

   PlayWinnerVoiceProbably(num);
}

void FixRankVoice(int num) {

    if (CurrentLevel == LevelIDs_Route101280)
        return;

    if (realChar == Characters_Tails)
        num = TailsRankVoices[CurrentLevelRank];

    PlayVoice(2, num);
}


static void __declspec(naked) FixCamEndPosASM(int pnum)
{
    __asm
    {
        push esi // pnum

        // Call your __cdecl function here:
        call FixCamEndPos

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
        call FixRankVoice
        add esp, 4
        jmp loc_44FD08
    }
}

void voicesFixes_Init() {

    HMODULE charaMod = GetModuleHandle(L"SA2CharSel");
    HMODULE charaModPlus = GetModuleHandle(L"CharacterSelectPlus");

    if (charaMod || charaModPlus)
        return;

    WriteJump((void*)0x44FC5E, PlayRankVoice);

    WriteCall((void*)0x44f864, FixCamEndPosASM);
    WriteCall((void*)0x450816, FixCamEndPosASM);
    WriteCall((void*)0x451017, FixCamEndPosASM);
    WriteCall((void*)0x4510af, FixCamEndPosASM);
}