#include "stdafx.h"

bool isSA1Voice = true;
bool isInfiniteFly = false;
HelperFunctions HelperFunctionsGlobal;


extern "C" {

	FunctionPointer(void, FUN_00673ae0, (), 0x00673ae0);

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		isInfiniteFly = config->getBool("Ability", "isInfiniteFly", false);
		delete config;

		HelperFunctionsGlobal = helperFunctions;

		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

		if (!MainCharObj1[0])
			return;

		float frame = MainCharObj2[0]->AnimInfo.field_A;
		float frame2 = MainCharObj2[0]->AnimInfo.field_14;
		float frame3 = MainCharObj2[0]->AnimInfo.field_18;
	
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}