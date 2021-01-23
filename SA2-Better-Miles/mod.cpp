#include "stdafx.h"


bool isInfiniteFly = false;
bool isCustomAnim = true;
bool isMechRemoved = false;
bool isMilesAdventure = false;

bool flySoundEffect = true;
bool jumpVoice = false;
bool flyVoice = false;
HelperFunctions HelperFunctionsGlobal;


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("General", "isInfiniteFly", false);
		isCustomAnim = config->getBool("General", "isCustomAnim", true);
		isMechRemoved = config->getBool("General", "isMechRemoved", false);
		isMilesAdventure = config->getBool("General", "isMilesAdventure", false);

		flySoundEffect = config->getBool("Audio", "flySoundEffect", true);
		jumpVoice = config->getBool("Audio", "jumpVoice", false);
		flyVoice = config->getBool("Audio", "flyVoice", false);

		delete config;

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 5)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Better Miles will not be available.\N Please update your Mod Loader for best experience.", "Better Miles Mod", MB_ICONWARNING);

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);

		if (isCustomAnim)
			HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\milesmtn.prs", "Resource\\gd_PC\\Animations\\milesmtn.prs");

		BetterMiles_Init();

		StoryEntry* story = (StoryEntry*)0x173A5E0;
		story->Type = 1;
		story->Level = LevelIDs_MetalHarbor;
		story->Character = Characters_Tails;
	}

	__declspec(dllexport) void __cdecl OnFrame() {

		EntityData1* data1 = MainCharObj1[0];
		CharObj2Base* co2 = MainCharObj2[0];

		/*if (Controllers[0].press & Buttons_Y)
			PlaySoundProbably(8193, 0, 0, 0);*/

	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}