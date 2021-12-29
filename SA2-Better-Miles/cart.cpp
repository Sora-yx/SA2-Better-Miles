#include "pch.h"

//unused, maybe someday though.

NJS_VECTOR SavePosCart;
Trampoline* CartExecuter_Main_t;


DataPointer(int, dword_1D970F8, 0x1D970F8);
DataPointer(int, dword_1D96F40, 0x1D96F40);
DataPointer(int, dword_174B070, 0x174B070);
DataPointer(int, currentCartChar, 0x1D970FC);
DataPointer(int, dword_FFBF6C, 0xFFBF6C);
VoidFunc(sub_61B130, 0x61B130);
VoidFunc(CartModule_Main, 0x61A390);
FunctionPointer(void*, init_CartPlayer, (int a1), 0x61AE20);

VoidFunc(Load_CartTimeOver, 0x623740);
cartStruct* cartPtr = nullptr;

DataPointer(int, cartTimeMaybe, 0x1D9442C);

Trampoline* sub_485850_t;

FunctionPointer(unsigned int, sub_485850, (ObjectMaster* a1, int* a2), 0x485850);

unsigned int __cdecl sub_485850_r(ObjectMaster* a1, int* a2) //fix crash when deleting player
{

	if (a1->MainSub == nullptr || !a2 || a2 + 52 == nullptr || (a2 + 52) + 44 == nullptr)
		return 0;


	TARGET_DYNAMIC(sub_485850)(a1, a2);
}


void __cdecl CartExecuter_Main_r(ObjectMaster* obj)
{

	TARGET_DYNAMIC(CartExecuter_Main)(obj);

	if (CurrentLevel != LevelIDs_KartRace) {

		obj->EntityData2 = obj->EntityData2;
		cartPtr = (cartStruct*)obj->EntityData2;
	}

}


void Load_CartTimeOver_r() {

	if (CurrentLevel != LevelIDs_Route101280 && CurrentLevel != LevelIDs_KartRace) {
		return;
	}

	return Load_CartTimeOver();
}

DataPointer(int, dword_19EF36C, 0x19EF36C);

void SetCartPlayerValue(char pNum) {


	cartTimeMaybe = 3600;
	dword_1D970F8 = 1;
	currentCartChar = 0; //force Tornado Kart Mode

	//what make the player clip the floor somehow
	//*(float*)0x171CAA4 = 1000000.0;

	*(int*)0x1934B87 = *(int*)0x174AFCB;
	*(int*)0x1934BE2 = *(int*)0x174AFCC;
	*(int*)0x174AFCC = 0;


	sub_61B130();
	CartModule_Main();

	dword_1D96F40 = 1;

	//dword_19EF36C = 1;

	MainCharObj1[pNum]->Action = 140;

	init_CartPlayer(dword_1D970F8);
}

DataArray(char, dword_1A2DB68, 0x1A2DB68, 0x8000u);

void DeleteAndLoadCart(char pNum) {

	LoadTextureList("cartObjModels", (NJS_TEXLIST*)0xFFA9C4);
	memset(dword_1A2DB68, 0, 0x8000u);
	SetCartPlayerValue(pNum);

	return;
}


void CallCart(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	switch (data->Action)
	{
	case 0:
	{
		SavePosCart = playerData->Position;
		DeleteAndLoadCart(pNum);
		InitCharacterSound();
		data->Action++;
	}
	break;
	case 1:

		if (++data->field_6 == 8)
		{
			//playerData->Position = SavePosCart;
			PlayVoice(2, 2433);
			ControllerEnabled[pNum] = 1;
			data->Action++;
		}
		break;
	default:
		DeleteObject_(obj);
		return;

	}
}

void Cart_CheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (GameState != GameStates_Ingame || !co2)
		return;

	if (Controllers[co2->PlayerNum].on & Buttons_Y && Controllers[co2->PlayerNum].press & Buttons_Left)
	{
		//CallMech(co2, data1);
		ObjectMaster* cart = LoadObject(2, "kart", CallCart, LoadObj_Data1);
		cart->Data1.Entity->Index = co2->PlayerNum;

		return;
	}
}

void Cart_HackInit() {
	//WriteCall((void*)0x61D139, Load_CartTimeOver_r);

	CartExecuter_Main_t = new Trampoline((int)CartExecuter_Main, (int)CartExecuter_Main + 0x6, CartExecuter_Main_r);
	sub_485850_t = new Trampoline((int)sub_485850, (int)sub_485850 + 0x6, sub_485850_r);
}