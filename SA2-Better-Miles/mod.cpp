#include "stdafx.h"

bool isSA1Voice = true;
bool isInfiniteFly = false;
HelperFunctions HelperFunctionsGlobal;

extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("Ability", "isInfiniteFly", false);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}