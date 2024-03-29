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


bool isMiles()
{
	if (MilesCO2Extern) {
		if (MainCharObj2[MilesCO2Extern->base.PlayerNum]->CharID == Characters_Tails)
			return true;
	}

	return false;
}

bool isMilesAttacking() {

	if (!isMiles())
		return false;

	EntityData1* data1 = MainCharObj1[MilesCO2Extern->base.PlayerNum];

	if (data1->Action == Flying || data1->Action == Jumping || data1->Action == Spinning || data1->Action == Rolling ||
		data1->Action == Bounce || data1->Action == BounceFloor || data1->Action == SpinningAir)
		{
			return true;
		}

	return false;
}

bool isMilesAttackingBox(char pnum) {

	EntityData1* data1 = MainCharObj1[pnum];

	if (!data1 || !isMiles())
		return false;


	if (data1->Action == Flying || data1->Action == Spinning || data1->Action == Rolling || data1->Action == Bounce || data1->Action == BounceFloor || data1->Action == SpinningAir)
		return true;

	return false;
}

bool isAttacking() {

	EntityData1* data1 = MainCharObj1[0];

	if (!data1)
		return false;

	if (isMilesAttacking() || data1->Action == Action_SpinCharge)
	{
		return true;
	}

	return false;
}

int DiffAngle(int ang0, int ang1)
{
	int v2; 

	v2 = (__int16)(ang1 - ang0);
	if (v2 < 0)
		v2 = -v2;
	return (unsigned __int16)v2;
}


std::unique_ptr<ModelInfo> LoadMDLSmartPtr(const char* name, ModelFormat format)
{
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

	std::unique_ptr<ModelInfo> temp = std::make_unique<ModelInfo>(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format) {
		PrintDebug("[Better Miles] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[Better Miles] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

ModelInfo* LoadMDL(const char* name, ModelFormat format) 
{
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

std::unique_ptr<AnimationFile> LoadANMSmartPtr(const char* name)
{
	std::string fullPath = "resource\\gd_PC\\animations\\";
	fullPath = fullPath + name + ".saanim";

	std::unique_ptr<AnimationFile> temp = std::make_unique<AnimationFile>(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (temp->getmodelcount()) 
	{
		PrintDebug("Done.\n\n");
		return temp;
	}
	else
	{
		PrintDebug("Failed.\n");
		return nullptr;
	}
}

void FreeMDL(ModelInfo* pointer) {
	if (pointer) delete(pointer);
}

void FreeAnim(AnimationFile* pointer) {
	if (pointer) delete pointer;
}

void SetCameraFacePlayer(char pNum, EntityData1* playerData, float zoom)
{
	sub_46C6D0(pNum, playerData->Position.x, playerData->Position.y, playerData->Position.z);
	RegisterCameraMode(pNum, 20);

	SetAdjustMode_(CameraData[0].currentCameraSlot, 0, 0);

	*(int*)0x1DCFDE0 = 3;
	*(int*)0x1DCFDE4 = 0;
	*(int*)0x1DCFDE8 = 0;
	*(float*)0x1DCFE1C = zoom; //Zoom
	CamEventPos = playerData->Position;
	CamEventAngleZ = 63488;
	CamEventAngleY = 0x4000 - playerData->Rotation.y;
}

bool isBossLevel() {
	return CurrentLevel >= LevelIDs_BigFoot || CurrentLevel == LevelIDs_SonicVsShadow1 ||
		CurrentLevel == LevelIDs_TailsVsEggman1 || CurrentLevel == LevelIDs_TailsVsEggman2
		|| CurrentLevel == LevelIDs_SonicVsShadow2 || CurrentLevel == LevelIDs_KnucklesVsRouge;
}

typedef AnimationIndex* (CALLBACK* anim) (void);

AnimationIndex* getCharAnim_r()
{
	if (!SA2Anim)
		return nullptr;

	anim Obj = (anim)GetProcAddress(SA2Anim, "GetCharacterAnim_r");

	if (Obj)
	{
		AnimationIndex* Result = Obj();
		return Result;
	}

	return nullptr;
}

typedef void(__cdecl* SetCharacterAnimFunc)(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);
void SetCharacterAnim_r(uint16_t Index, uint16_t Count, NJS_MOTION* Animation)
{
	if (!SA2Anim)
		return;

	SetCharacterAnimFunc Obj = (SetCharacterAnimFunc)GetProcAddress(SA2Anim, "SetCharacterAnim");

	if (Obj)
	{
		Obj(Index, Count, Animation);
	}
}

typedef bool (*isChar) (uint8_t charID);

bool isSA1Char(uint8_t charID) {

	if (!SA1Char)
		return false;

	isChar Obj = (isChar)GetProcAddress(SA1Char, "isSA1Char");

	if (Obj)
	{
		return Obj(charID);
	}

	return false;
}

bool isTailsAI()
{
	for (int i = 0; i < 4; i++)
	{
		if (!MainCharObj1[i] || MainCharObj1[i]->field_2 != 3)
			continue;

		if (MainCharObj2[i]->CharID == Characters_Tails)
			return true;
	}

	return false;
}


void njRotateXYZ(NJS_MATRIX_PTR m, Angle angx, Angle angy, Angle angz)
{
	njRotateZ(_nj_current_matrix_ptr_, angz);
	njRotateY(_nj_current_matrix_ptr_, angy);
	njRotateX(_nj_current_matrix_ptr_, angx);
}

bool isKeyboard()
{
	if (MainUserConfig != nullptr)
	{
		if (MainUserConfig->data.field_28 == 0)
			return true;
	}

	return false;
}

void njAddVector(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x + vs->x;
	vd->y = vs->y + vd->y;
	vd->z = vs->z + vd->z;
}

void njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs)
{
	vd->x = vd->x - vs->x;
	vd->y = vd->y - vs->y;
	vd->z = vd->z - vs->z;
}

int __cdecl AdjustAngle(__int16 bams_a, unsigned __int16 bams_b, int limit)
{
	int result; // eax
	__int16 v4; // cx

	result = bams_b;
	v4 = bams_b - bams_a;
	if ((bams_b - bams_a) > limit || v4 < -limit)
	{
		if (v4 >= 0)
		{
			result = (limit + bams_a);
		}
		else
		{
			result = (bams_a - limit);
		}
	}
	return result;
}

Float njSqrt(Float n)
{
	if (n < 0.0f)
	{
		return -sqrtf(n * -1.0f);
	}
	else
	{
		return sqrtf(n);
	}
}