#include "pch.h"

HelperFunctions HelperFunctionsGlobal;
const char* error = "[Better Miles]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";

HMODULE SA2Anim = NULL;
HMODULE SA1Char = NULL;


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(15);

		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "Better Miles", MB_ICONWARNING);
		}

		if (!flySoundEffect)
			WriteData<5>((void*)0x752e16, 0x90);

		SA2Anim = GetModuleHandle(L"SA2-Anim-Break");
		SA1Char = GetModuleHandle(L"SA2-SA1-Chars");

		ReadConfig(path); //get mod settings by the user


		init_BassSound();

		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\se_ch_te\\2.csb", "Resource\\gd_PC\\Sounds\\se_ch_te\\2.csb");
		HelperFunctionsGlobal.ReplaceFile("Resource\\gd_PC\\MLT\\chao_chara_te\\2.csb", "Resource\\gd_PC\\Sounds\\chao_chara_te\\2.csb");
		BetterMiles_Init();
	}

	__declspec(dllexport) void __cdecl OnFrame() {

		RunCustomSounds();
		if (Controllers[0].on & Buttons_L && Controllers[0].on & Buttons_R && Controllers[0].press & Buttons_X)
		{
			//AwardWin(0);
		}
	}


	__declspec(dllexport) void __cdecl OnInitEnd()
	{
		FreeAllCustomSounds();
		Delete_Tornado();
		Delete_TornadoTransform();
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}