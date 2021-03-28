#include "stdafx.h"

bool isCustomPhysics = true;
bool isCustomAnim = true;
bool isMechRemoved = false;
bool isMilesAdventure = false;

bool isInfiniteFly = false;
bool isLightDash = true;
bool isBounce = true;

bool flySoundEffect = true;
bool jumpVoice = false;

HelperFunctions HelperFunctionsGlobal;

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isCustomPhysics = config->getBool("General", "isCustomPhysics", true);
		isCustomAnim = config->getBool("General", "isCustomAnim", true);
		isMechRemoved = config->getBool("General", "isMechRemoved", true);
		isMilesAdventure = config->getBool("General", "isMilesAdventure", false);

		isInfiniteFly = config->getBool("Abilities", "isInfiniteFly", false);
		isLightDash = config->getBool("Abilities", "isLightDash", true);
		isBounce = config->getBool("Abilities", "isBounce", true);

		flySoundEffect = config->getBool("Audio", "flySoundEffect", true);
		jumpVoice = config->getBool("Audio", "jumpVoice", false);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 5)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Better Miles will not be available.\N Please update your Mod Loader for best experience.", "Better Miles Mod", MB_ICONWARNING);

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);

		if (isCustomAnim)
			HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\milesmtn.prs", "Resource\\gd_PC\\Animations\\milesmtn.prs");

		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\se_ch_te\\2.csb", "Resource\\gd_PC\\Sounds\\se_ch_te\\2.csb");
		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\chao_chara_te\\2.csb", "Resource\\gd_PC\\Sounds\\chao_chara_te\\2.csb");
		BetterMiles_Init();
		InitLightDashStuff();
	}

	__declspec(dllexport) void __cdecl OnFrame() {
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}