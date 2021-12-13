#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
const char* error = "[Better Miles]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(10);

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "Better Miles", MB_ICONWARNING);
		}

		ReadConfig(path); //get mod settings by the user

		if (HelperFunctionsGlobal.Version < 5)
			MessageBoxA(MainWindowHandle, "WARNING: Your version of the Mod Loader is old, some functionality of Better Miles will not be available.\N Please update your Mod Loader for best experience.", "Better Miles Mod", MB_ICONWARNING);

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);

		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\se_ch_te\\2.csb", "Resource\\gd_PC\\Sounds\\se_ch_te\\2.csb");
		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\chao_chara_te\\2.csb", "Resource\\gd_PC\\Sounds\\chao_chara_te\\2.csb");
		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

	}



	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}