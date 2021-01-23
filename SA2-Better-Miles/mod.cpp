#include "stdafx.h"

bool flySoundEffect = true;
bool isInfiniteFly = false;
bool isCustomAnim = true;
bool isMechRemoved = false;
bool isMilesAdventure = false;
HelperFunctions HelperFunctionsGlobal;


extern "C" {



	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("General", "isInfiniteFly", false);
		flySoundEffect = config->getBool("General", "flySoundEffect", true);
		isCustomAnim = config->getBool("General", "isCustomAnim", true);
		isMechRemoved = config->getBool("General", "isMechAllowed", false);
		isMilesAdventure = config->getBool("General", "isMilesAdventure", false);
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
		story->Level = LevelIDs_GreenHill;
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