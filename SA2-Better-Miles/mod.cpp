#include "stdafx.h"


extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{

		WriteData<5>((void*)0x752d9a, 0x90); //Remove tails voice when doing spin attack;


		//Spin Attack stuff
		WriteData<7>((int*)0x74ed0e, 0x90); //remove reset anim for spin attack
		WriteData<4>((int*)0x74ed0a, 0x90); //remove reset action for spin attack.
		WriteData<1>((int*)0xa0dbf2, 0x80); //Increase transition speed (from 0.125 to 1.0)
		WriteData<1>((int*)0xa0dbf3, 0x3F);		
		WriteData<1>((int*)0xa0dbee, 0x5E);

		//WriteData<1>((int*)0xa0dbf6, 0xC0);  //Animation Speed
		//WriteData<1>((int*)0xa0dbf7, 0x3F);

		PhysicsArray[Characters_Tails].AirAccel = 0.060;
		PhysicsArray[Characters_Tails].Brake = -0.30;
		PhysicsArray[Characters_Tails].HangTime = 60;
		PhysicsArray[Characters_Tails].FloorGrip = 2.0;
		PhysicsArray[Characters_Tails].JumpAddSpeed = 0.076;
		PhysicsArray[Characters_Tails].JumpSpeed = 2.0;
		PhysicsArray[Characters_Tails].GroundAccel = 0.14;

		WriteCall((void*)0x74e1cf, Tails_FlyStartASM);		
		WriteCall((void*)0x74e513, Tails_FlyStartASM);		
		WriteCall((void*)0x751f5e, Tails_FlyStartASM);		
		WriteCall((void*)0x75225e, Tails_FlyStartASM);


		//WriteData<5>((void*)0x74d818, 0x90);
	}


	__declspec(dllexport) void __cdecl OnFrame()
	{

		Miles_OnFrames();
	}



	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}