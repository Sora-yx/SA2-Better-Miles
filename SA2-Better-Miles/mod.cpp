#include "stdafx.h"

bool flySoundEffect = true;
bool isInfiniteFly = false;
bool isCustomAnim = true;
HelperFunctions HelperFunctionsGlobal;


extern "C" {

	FunctionPointer(void, FUN_00673ae0, (), 0x00673ae0);

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("General", "isInfiniteFly", false);
		flySoundEffect = config->getBool("Generam", "flySoundEffect", true);
		isCustomAnim = config->getBool("General", "isCustomAnim", true);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 5)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Better Miles will not be available.\N Please update your Mod Loader for best experience.", "Better Miles Mod", MB_ICONWARNING);

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);

		if (isCustomAnim)
			HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\milesmtn.prs", "Resource\\gd_PC\\Animations\\milesmtn.prs");

		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {


	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}