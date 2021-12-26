#include "pch.h"

NJS_VECTOR SavePosCart;

DataPointer(int, dword_1D970F8, 0x1D970F8);
DataPointer(int, dword_174B070, 0x174B070);
DataPointer(int, dword_1D970FC, 0x1D970FC);
DataPointer(int, dword_FFBF6C, 0xFFBF6C);
VoidFunc(sub_61B130, 0x61B130);
VoidFunc(CartModule_Main, 0x61A390);
FunctionPointer(void*, init_CartPlayer, (int a1), 0x61AE20);

void SetCartPlayerValue() {


	dword_1D970F8 = 0;
	if (dword_174B070 >= 3)
	{
		dword_1D970FC = Characters_Rouge;
	}
	else
	{
		dword_1D970FC = dword_174B070 + 2;
	}

	//what make the player clip the floor somehow
	*(float*)0x171CAA4 = 1000000.0;

	*(int*)0x1934B87 = *(int*)0x174AFCB;
	*(int*)0x1934BE2 = *(int*)0x174AFCC;
	*(int*)0x174AFCC = 0;

	sub_61B130();
	CartModule_Main();
	//init_CartPlayer(dword_1D970F8);

}

DataArray(char, dword_1A2DB68, 0x1A2DB68, 0x8000u);

void DeleteAndLoadCart(char pNum) {

	LoadTextureList("cartObjModels", (NJS_TEXLIST*)0xFFA9C4);
	memset(dword_1A2DB68, 0, 0x8000u);
	SetCartPlayerValue();

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
			playerData->Position = SavePosCart;
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
		ObjectMaster* tornado = LoadObject(2, "kart", CallCart, LoadObj_Data1);
		tornado->Data1.Entity->Index = co2->PlayerNum;

		return;
	}
}