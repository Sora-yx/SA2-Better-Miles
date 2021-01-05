#include "stdafx.h"


bool isSA1Voice = true;
bool isInfiniteFly = false;


extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("Ability", "isInfiniteFly", false);
		delete config;

		BetterMiles_Init();
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}