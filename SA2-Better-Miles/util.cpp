#include "pch.h"

const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

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

bool isSuperForm(char pID) {
	if (MainCharObj2[pID]->CharID == Characters_Tails && MainCharObj2[pID]->Upgrades & Upgrades_SuperSonic || CurrentLevel == LevelIDs_FinalHazard)
	{
		return true;
	}

	return false;
}



void PlayerMoveStuff(EntityData1* a1, EntityData2* a2, CharObj2Base* a3) {
	PGetSpeed(a1, a3, a2);
	PSetPosition(a1, a2, a3);
	PResetPosition(a1, a2, a3);
	return;
}


void sub_4273B0(NJS_VECTOR* a1, NJS_VECTOR* a2, float* a3)
{
	Float v3; // ST00_4
	Float v4; // ST04_4

	v3 = a3[4] * a1->x + a3[5] * a1->y + a3[6] * a1->z;
	v4 = a3[8] * a1->x + a3[9] * a1->y + a3[10] * a1->z;
	a2->x = a3[1] * a1->y + *a3 * a1->x + a3[2] * a1->z;
	a2->y = v3;
	a2->z = v4;
}

int IsPlayerInsideSphere(NJS_VECTOR* position, float a2)
{
	int player; // esi
	EntityData1* v3; // eax
	CollisionInfo* v4; // eax
	float* v5; // eax
	double v6; // st7
	float posX; // [esp+4h] [ebp-1Ch]
	float posY; // [esp+8h] [ebp-18h]
	float posZ; // [esp+Ch] [ebp-14h]
	float v11; // [esp+10h] [ebp-10h]
	NJS_VECTOR a1; // [esp+14h] [ebp-Ch] BYREF

	posX = position->x;
	player = 0;
	posY = position->y;
	posZ = position->z;
	while (1)
	{
		v3 = MainCharObj1[player];
		if (v3)
		{
			v4 = v3->Collision;
			if (v4)
			{
				v5 = (float*)&v4->CollisionArray->kind;
				v6 = v5[2];
				v5 += 3;
				a1.x = v6 - posX;
				a1.y = *v5 - posY;
				a1.z = v5[1] - posZ;
				v11 = njScalor(&a1) - a2;
				if (v11 < 0.0)
				{
					break;
				}
			}
		}
		if (++player >= 2)
		{
			return 0;
		}
	}
	return player + 1;
}

bool isMilesAttacking() {
	if (MainCharObj2[0]->CharID != Characters_Tails)
		return false;

	EntityData1* data1 = MainCharObj1[0];

	if (data1->Action == Flying || data1->Action == Jumping || data1->Action == Spinning || data1->Action == Rolling || data1->Action == BounceFloor)
		return true;

	return false;
}

bool isMilesAttackingBox() {
	if (MainCharObj2[0]->CharID != Characters_Tails)
		return false;

	EntityData1* data1 = MainCharObj1[0];

	if (data1->Action == Flying || data1->Action == Spinning || data1->Action == Rolling || data1->Action == BounceFloor)
		return true;

	return false;
}

int DiffAngle(int ang0, int ang1)
{
	int v2; // r11

	v2 = (__int16)(ang1 - ang0);
	if (v2 < 0)
		v2 = -v2;
	return (unsigned __int16)v2;
}

//Load Object File
ModelInfo* LoadMDL(const char* name, ModelFormat format) {
	std::string fullPath;

	if (format == ModelFormat_Chunk) {
		fullPath = "resource\\gd_PC\\Models\\";
	}

	fullPath += name;

	switch (format) {
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}

	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format) {
		PrintDebug("[Better Miles] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[Better Miles] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

void LoadAnimation(AnimationFile** info, const char* name, const HelperFunctions& helperFunctions) {
	std::string fullPath = "resource\\gd_PC\\animations\\";
	fullPath = fullPath + name + ".saanim";

	AnimationFile* anm = new AnimationFile(helperFunctions.GetReplaceablePath(fullPath.c_str()));

	if (anm->getmodelcount() == 0) {
		delete anm;
		*info = nullptr;
	}
	else {
		*info = anm;
	}
};

AnimationFile* LoadAnim(const char* name) {
	std::string fullPath = "resource\\gd_PC\\animations\\";

	fullPath = fullPath + name + ".saanim";

	AnimationFile* file = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (file->getmotion() != nullptr) {
		PrintDebug("[SA2 Better Miles] Loaded animation: %s.", name);
	}
	else {
		PrintDebug("[SA2 Better Miles] Failed loading animation: %s.", name);
	}

	return file;
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) delete(pointer);
}

void FreeAnim(AnimationFile* pointer) {
	if (pointer) delete pointer;
}

void __fastcall njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x - vs->x;
	vd->y = vd->y - vs->y;
	vd->z = vd->z - vs->z;
}

void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) {
	NJS_VECTOR unit = *to;


	//*outy = static_cast<Angle>(atan2f(unit.x, unit.z) * 65536.0f * 0.1591549762031479f);

	if (outx) {
		if (from->y == to->y) {
			*outx = 0;
		}
		else {
			Float len = 1.0f / sqrt(unit.z * unit.z + unit.x * unit.x + unit.y * unit.y);

			*outx = static_cast<Angle>((acos(len * 3.3499999f) * 65536.0f * 0.1591549762031479f)
				- (acos(-(len * unit.y)) * 65536.0f * 0.1591549762031479f));
		}
	}
}

void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy) {
	LookAt(from, to, outx, outy);

	if (outy) {
		*outy = -(*outy) + 0x4000;
	}
}

void SetCameraFacePlayer(char pNum, EntityData1* playerData, float zoom)
{
	sub_46C6D0(pNum, playerData->Position.x, playerData->Position.y, playerData->Position.z);
	SetCameraEvent(pNum, 20);
	DoSomethingWithCam(*(DWORD*)&CameraData.gap1AC[9432 * pNum + 168], 0, 0);
	*(int*)0x1DCFDE0 = 3;
	*(int*)0x1DCFDE4 = 0;
	*(int*)0x1DCFDE8 = 0;
	*(float*)0x1DCFE1C = zoom; //Zoom
	CamPosAgain = playerData->Position;
	CamAngleZ = 63488;
	CamAngleY = 0x4000 - playerData->Rotation.y;
}

bool isBossLevel() {
	return CurrentLevel >= LevelIDs_BigFoot || CurrentLevel == LevelIDs_SonicVsShadow1 ||
		CurrentLevel == LevelIDs_TailsVsEggman1 || CurrentLevel == LevelIDs_TailsVsEggman2
		|| CurrentLevel == LevelIDs_SonicVsShadow2;
}
