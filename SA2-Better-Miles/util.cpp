#include "pch.h"

void DoNextAction_r(int playerNum, char action, int unknown)
{
	EntityData1* v3; // eax

	v3 = MainCharObj1[playerNum];
	if (v3)
	{
		v3->Status |= Status_DoNextAction;
		v3->NextAction = action;
		MainCharObj2[playerNum]->field_28 = unknown;
	}
}

bool isRando() {
	HMODULE randoMod = GetModuleHandle(L"Rando");

	if (randoMod)
		return true;

	return false;
}

bool isCharaSelect() {
	HMODULE charaMod = GetModuleHandle(L"SA2CharSel");
	HMODULE charaModPlus = GetModuleHandle(L"CharacterSelectPlus");

	if (charaMod || charaModPlus)
		return true;

	return false;
}

bool isSA1Tails() {

	HMODULE SA1 = GetModuleHandle(L"sa1-tails");

	if (SA1)
		return true;

	return false;
}

bool isSuperForm() {
	if (MainCharObj2[0]->CharID == Characters_Tails && MainCharObj2[0]->Upgrades & Upgrades_SuperSonic || CurrentLevel == LevelIDs_FinalHazard)
	{
		return true;
	}

	return false;
}