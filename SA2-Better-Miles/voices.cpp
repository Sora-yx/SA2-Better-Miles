#include "stdafx.h"

static const void* const PlayWinnerVoicePtr = (void*)0x43ECA0;
DataArray(int, TailsRankVoices, 0x173B7E4, 5);
DataPointer(char, CurrentLevelRank, 0x174B001);

char realChar = 0;
void FixEndCamPosAndVoice(int num) {

    if (CurrentLevel == LevelIDs_Route101280)
        return;

    realChar = MainCharObj2[0]->CharID;

   if (MainCharObj2[0]->CharID == Characters_Tails) {
       PlayVoice(2, num = CurrentLevel == LevelIDs_TailsVsEggman1 ? 1715 : 1703); //"I did it" 
       MainCharObj2[0]->CharID = Characters_Rouge; //Trick the game to make it think we are playing Rouge so it gives a good camera for victory pose.
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
        call FixEndCamPosAndVoice

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

void Init_VoicesFixes() {

    HMODULE charaMod = GetModuleHandle(L"SA2CharSel");
    HMODULE charaModPlus = GetModuleHandle(L"CharacterSelectPlus");

    if (!charaMod && !charaModPlus) {
        WriteJump((void*)0x44FC5E, PlayRankVoice);
    }

    WriteCall((void*)0x44f864, FixCamEndPosASM);
    WriteCall((void*)0x450816, FixCamEndPosASM);
    WriteCall((void*)0x451017, FixCamEndPosASM);
    WriteCall((void*)0x4510af, FixCamEndPosASM);

    if (!jumpVoice)
        WriteData<5>((void*)0x751C90, 0x90); //remove tails voice when jumping
}
