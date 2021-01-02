#include "stdafx.h"


extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		//PhysicsArray[0].HangTime = 60;
		WriteData<5>((void*)0x752d9a, 0x90); //Remove tails voice when doing spin attack;


		//Spin Attack stuff
		WriteData<7>((int*)0x74ed0e, 0x90); //remove reset anim for spin attack
		WriteData<4>((int*)0x74ed0a, 0x90); //remove reset action for spin attack.
		WriteData<1>((int*)0xa0dbf2, 0x80); //Increase transition speed (from 0.125 to 1.0)
		WriteData<1>((int*)0xa0dbf3, 0x3F);
		//WriteData<1>((int*)0xa0dbf6, 0xC0);  //Animation Speed
		//WriteData<1>((int*)0xa0dbf7, 0x3F);
	}


	__declspec(dllexport) void __cdecl OnFrame()
	{

		Miles_OnFrames();
	}



	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}