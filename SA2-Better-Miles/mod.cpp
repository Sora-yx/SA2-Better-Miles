#include "stdafx.h"


bool isSA1Voice = true;


extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		BetterMiles_Init();
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}