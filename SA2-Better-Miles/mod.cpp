#include "stdafx.h"

bool flySoundEffect = true;
bool isInfiniteFly = false;
HelperFunctions HelperFunctionsGlobal;


extern "C" {

	FunctionPointer(void, FUN_00673ae0, (), 0x00673ae0);

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("Ability", "isInfiniteFly", false);
		flySoundEffect = config->getBool("Sound", "flySoundEffect", true);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);


		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {


	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}