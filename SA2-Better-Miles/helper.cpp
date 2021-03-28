#include "stdafx.h"

Trampoline* CheckBreakObject_t;
Trampoline* MysticMelody_t;
Trampoline* Dynamite_t;
Trampoline* DynamiteHiddenBase_t;
Trampoline* DynamiteSandOcean_t;
Trampoline* PrisonLaneDoor_t;
Trampoline* PrisonLaneDoor4_t;
Trampoline* SuperAura_t;
Trampoline* DoorIG_t;
Trampoline* DoorIG2_t;
Trampoline* RocketIG_t;
Trampoline* BrokenDownSmoke_t;
Trampoline* MetalBox_t;
Trampoline* MetalBoxGravity_t;

static const void* const GetAnalogPtr2 = (void*)0x45A870;
inline signed int GetAnalogASM2(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude)
{
	signed int result;
	__asm
	{
		push[magnitude]
		push[angle]
		push[co2]
		mov eax, [data]
		call GetAnalogPtr2
		mov result, eax
		add esp, 12
	}
	return result;
}

signed int CallGetAnalog(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude) {
	return GetAnalogASM2(data, co2, angle, magnitude);
}

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

//signed int __usercall njPushMatrix@<eax>(NJS_MATRIX_PTR m@<ecx>)
static const void* const njPushMatrixPtr = (void*)0x77FE10;
static inline signed int njPushMatrixMaybe(NJS_MATRIX_PTR m)
{
	signed int result;
	__asm
	{
		mov ecx, [m]
		call njPushMatrixPtr
		mov result, eax
	}
	return result;
}


static const void* const sub428A30ptr = (void*)0x428A30;
static inline void njTranslatePosition(NJS_VECTOR* a1)
{
	__asm
	{
		mov eax, [a1]
		call sub428A30ptr
	}
}

void CheckAndDisplayAfterImage(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3)
{
	NJS_OBJECT* v3; // edi
	NJS_MATRIX_PTR v4; // ebx

	if ((FrameCountIngame & 1) == 0 && a2->CharID == Characters_Tails && CharacterModels[208].Model)
	{
		v3 = CharacterModels[208].Model;
		njPushMatrixMaybe(flt_25F02A0);

		njTranslatePosition(&a1->Position);
		v4 = nj_current_matrix_ptr_;
		if (a1->Rotation.z)
		{
			njRotateZ((float*)nj_current_matrix_ptr_, a1->Rotation.z);
		}
		if (a1->Rotation.x)
		{
			njRotateX((float*)v4, a1->Rotation.x);
		}
		if (a1->Rotation.y != 0x8000)
		{
			njRotateY((float*)v4, 0x8000 - a1->Rotation.y);
		}
		if (!TwoPlayerMode)
		{
			PlayerAfterImageMaybe(v3, 0, a3->TextureList, 0.0, 0);
			v4 = nj_current_matrix_ptr_;
		}
		if ((unsigned int)(v4 - 12) >= dword_267053C)
		{
			nj_current_matrix_ptr_ = v4 - 12;
		}
	}
}

static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static inline char PlaySound3DThingMaybeASM(int id, NJS_VECTOR* pos, int a3, char a4, char a5)
{
	char result;
	__asm
	{
		push[a5]
		push[a4]
		push[a3]
		mov esi, [pos]
		mov edi, [id]
		call Sub4372E0Ptr
		add esp, 12
		mov result, al
	}
	return result;
}

char Play3DSoundPosThing(int id, NJS_VECTOR* pos, int a3, char a4, char a5) {

	return PlaySound3DThingMaybeASM(id, pos, a3, a4, a5);
}

static const void* const PGetAccelAirPtr = (void*)0x45D770;
static inline void PlayerGetAccelerationAirASM(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2)
{
	__asm
	{
		push[data2]
		mov eax, [co2]
		mov ecx, a1 // a1

		// Call your __cdecl function here:
		call PGetAccelAirPtr

		add esp, 4 // a3
	}
}

void PlayerGetAccelerationAir(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2) {
	return PlayerGetAccelerationAirASM(a1, co2, data2);
}

static const void* const PResetAnglePtr = (void*)0x460260;
static inline void PlayerResetAngleASM(EntityData1* a1, CharObj2Base* co2)
{
	__asm
	{
		mov ebx, [co2]
		mov eax, [a1] // a1
		call PResetAnglePtr
	}
}

void PlayerResetAngle(EntityData1* a1, CharObj2Base* co2)
{
	return PlayerResetAngleASM(a1, co2);
}

void DoNextAction_R(int playerNum, char action, int unknown) {
	EntityData1* v3 = MainCharObj1[playerNum];

	if (v3)
	{
		v3->Status |= Status_DoNextAction;
		v3->NextAction = action;
		MainCharObj2[playerNum]->field_28 = unknown;
	}
}

static const void* const PGetSpeedPtr = (void*)0x460860;
static inline void PlayerGetSpeedASM(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2)
{
	__asm
	{
		push[data2] // a3
		mov ebx, co2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call PGetSpeedPtr

		add esp, 4 // a3
	}
}

void PlayerGetSpeed(EntityData1* a1, CharObj2Base* co2, EntityData2_R* data2)
{
	PlayerGetSpeedASM(a1, co2, data2);
}

static const void* const PSetPositionptr = (void*)0x4616E0;
static inline int PSetPositionASM(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
	int result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call PSetPositionptr
		add esp, 8
		mov result, eax
	}
	return result;
}

int PlayerSetPosition(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
	return PSetPositionASM(a1, a2, a3);
}

static const void* const sub_469050Ptr = (void*)0x469050;
static inline void PResetPositionASM(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		mov ebx, a2 // a2
		mov eax, a1 // a1
		call sub_469050Ptr
		add esp, 4 // a2
	}
}

void PlayerResetPosition(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3) {
	PResetPositionASM(a1, a2, a3);
}

void PlayerMoveStuff(EntityData1* a1, EntityData2_R* a2, CharObj2Base* a3) {
	PlayerGetSpeed(a1, a3, a2);
	PlayerSetPosition(a1, a2, a3);
	PlayerResetPosition(a1, a2, a3);
	return;
}

static const void* const PlayerCheckFallGravityPtr = (void*)0x4751D0;
static inline int PlayerCheckFallGravityStuff(EntityData1* a1, int a2, EntityData2_R* a3, CharObj2Base* a4)
{
	int result;
	__asm
	{
		push[a4] // a4
		push[a3] // a3
		mov ecx, [a2] // a1
		mov eax, [a1]
		// Call your __cdecl function here:
		call PlayerCheckFallGravityPtr
		add esp, 12 // a1<eax> is also used for return value
		mov result, eax
	}
	return result;
}

int CallPlayerCheckFallGravityStuff(EntityData1* a1, int a2, EntityData2_R* a3, CharObj2Base* a4) {
	return PlayerCheckFallGravityStuff(a1, a2, a3, a4);
}

static const void* const VibeThingPtr = (void*)0x438E70;
static inline void VibeThingASM(int a1, signed int a2, int a3, signed int a4)
{
	__asm
	{
		push[a4] // int a4
		mov ecx, a3 // a3
		mov edx, a2 // int a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call VibeThingPtr
		add esp, 4 // int a4
	}
}

void CallVibeThing(int a1, signed int a2, int a3, signed int a4)
{
	VibeThingASM(a1, a2, a3, a4);
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

Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{
	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];

	if (isMilesAttackingBox() && GetCollidingPlayer(obj))
		return 1;

	FunctionPointer(Bool, original, (ObjectMaster * obj, ObjectMaster * other), CheckBreakObject_t->Target());
	return original(obj, other);
}

static const void* const loc_776339 = (void*)0x776339;
static const void* const loc_776580 = (void*)0x776580;
__declspec(naked) void  CheckBreakCGGlasses() {
	if (MainCharObj1[0]->Action == 13 || isMilesAttacking())
	{
		_asm jmp loc_776339
	}
	else {
		_asm jmp loc_776580
	}
}

static const void* const SetMysticMelodyActionPtr = (void*)0x475F00;
static inline void SetMysticMelodyAction(CharObj2Base* a1, EntityData1* a2)
{
	__asm
	{
		mov ecx, [a2]
		mov eax, [a1]
		call SetMysticMelodyActionPtr
	}
}

void PlayMysticMelody(ObjectMaster* obj)
{
	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data = MainCharObj1[0];

	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 15))
	{
		if (data->NextAction == 0 && co2->CharID == Characters_Tails) {
			if (Controllers[co2->PlayerNum].on & (Buttons_X | Buttons_B) && (data->Action == 0 || data->Action == 60))
				SetMysticMelodyAction(co2, data);
		}
	}

	ObjectFunc(origin, MysticMelody_t->Target());
	origin(obj);
}

static const void* const loc_776D23 = (void*)0x776D23;
static const void* const loc_776D5F = (void*)0x776D5F;
__declspec(naked) void  CheckGravitySwitch() {
	if (MainCharObj1[0]->Action == 0x53 || (Controllers[0].press & (Buttons_X | Buttons_B)))
	{
		_asm jmp loc_776D23
	}
	else {
		_asm jmp loc_776D5F
	}
}

void ForceMiles(int player) {
	if (!TwoPlayerMode && CurrentLevel != LevelIDs_Route101280 && CurrentLevel != LevelIDs_KartRace
		&& CurrentLevel != LevelIDs_TailsVsEggman1 && CurrentLevel != LevelIDs_TailsVsEggman2) {
		CurrentCharacter = Characters_Tails;
		LoadTails(player);
	}
	else {
		CurrentCharacter = Characters_MechTails;
		LoadMechTails(player);
	}
}

void CheckBreakDynamite(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->Action == 0 && isMilesAttacking() && GetCollidingPlayer(obj)) {
			data->Status |= 4u;
			obj->EntityData2->gap_44[0] = 0;
		}
	}

	ObjectFunc(origin, Dynamite_t->Target());
	origin(obj);
}

void CheckBreakDynamiteHiddenBase(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->NextAction != 7 && isMilesAttacking() && GetCollidingPlayer(obj)) {
			data->field_6 = 0;
			data->NextAction = 7;
		}
	}

	ObjectFunc(origin, DynamiteHiddenBase_t->Target());
	origin(obj);
}

void CheckBreakDynamiteSandOcean(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (obj) {
		if (data->Action == 0 && isMilesAttacking() && GetCollidingPlayer(obj)) {
			data->Status |= 4u;
			obj->EntityData2->gap_44[0] = 0;
		}
	}

	ObjectFunc(origin, DynamiteSandOcean_t->Target());
	origin(obj);
}

void CheckAndOpenPrisonLaneDoor(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	EntityData2* data2 = obj->Data2.Entity;

	if (obj) {
		if (MainCharObj2[0]->CharID != Characters_Tails)
			return;

		if (data->Action == 0 && data->Rotation.x == 3)
		{
			data->Rotation.x = 32;
		}
		else  if (data->Action < 1 && GetCollidingPlayer(obj)) {
			data->Rotation.x = 3;
			data->Action = 1;
		}
	}
}

void CheckPrisonLaneDoor(ObjectMaster* obj) {
	CheckAndOpenPrisonLaneDoor(obj);

	ObjectFunc(origin, PrisonLaneDoor_t->Target());
	origin(obj);
}

void CheckPrisonLaneDoor4(ObjectMaster* obj) {
	CheckAndOpenPrisonLaneDoor(obj);

	ObjectFunc(origin, PrisonLaneDoor4_t->Target());
	origin(obj);
}

void CheckAndSetHackObjectMiles() {
	if (CurrentCharacter == Characters_MechTails || CurrentCharacter == Characters_MechEggman) {
		WriteData<1>((int*)0x715b58, 0x6);
		WriteData<1>((int*)0x715aa8, 0x6);
		WriteData<1>((int*)0x7158bf, 0x6);

		WriteData<1>((int*)0x79b427, 0x6);
		WriteData<1>((int*)0x79b959, 0x6);
		WriteData<1>((int*)0x79be57, 0x6);
		return; //if one player has a mech, we don't need to hack the door
	}

	//hack so non mech character can destroy the doors
	if (CurrentLevel == LevelIDs_HiddenBase) {
		//Hidden base door Col Stuff
		WriteData<1>((int*)0x715b58, 0x1);
		WriteData<1>((int*)0x715aa8, 0x1);
		WriteData<1>((int*)0x7158bf, 0x1);
	}

	if (CurrentLevel == LevelIDs_CannonsCoreT) {
		//CC door col Stuff
		WriteData<1>((int*)0x79b427, 0x1);
		WriteData<1>((int*)0x79b959, 0x1);
		WriteData<1>((int*)0x79be57, 0x1);
	}

	return;
}

void CheckAndOpenIronGateDoor(ObjectMaster* obj) {
	if (MainCharObj2[0]->CharID != Characters_Tails)
		return;

	EntityData1* data = obj->Data1.Entity;

	if (GetCollidingPlayer(obj)) {
		data->NextAction = 15;
	}
}

void doorIG_r(ObjectMaster* obj) {
	CheckAndOpenIronGateDoor(obj);

	ObjectFunc(origin, DoorIG_t->Target());
	origin(obj);
}

void doorIG2_r(ObjectMaster* obj) {
	CheckAndOpenIronGateDoor(obj);

	ObjectFunc(origin, DoorIG2_t->Target());
	origin(obj);
}

void rocketIG_r(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (MainCharObj2[0]->CharID == Characters_Tails) {
		if (GetCollidingPlayer(obj) && isMilesAttacking() && data->Action == 5)
		{
			data->Action = 6;
		}
	}

	ObjectFunc(origin, RocketIG_t->Target());
	origin(obj);
}

void Super_Aura_r(ObjectMaster* obj) {
	if (MainCharacter[1]) {
		EntityData2* data2 = MainCharacter[1]->Data2.Entity;
		word_170ACEE = word_170ACEE & 0xC000 | ((int(data2->CharacterData) != 10 ? 0 : 6)
			+ (data2[13].field_1C)
			+ 3);
	}

	ObjectFunc(origin, SuperAura_t->Target());
	origin(obj);
}

void LoadSuperFormFinalBattle() {
	if (MainCharacter[1])
		DeleteObject_(MainCharacter[1]);

	LoadSuperShadow();
	InitPlayer(1);

	if (MainCharacter[0])
		DeleteObject_(MainCharacter[0]);

	LoadTails(0);
	TailsCharObj2* co2Miles = (TailsCharObj2*)MainCharObj2[0];
	MainCharacter[0]->SomethingSub = Super_Something;
	co2Miles->base.Upgrades = Upgrades_SuperSonic;
	LastBossPlayerManager_Load();
	InitPlayer(0);
	return;
}

void BrokenDownSmoke_r(ObjectMaster* a1) {
	if (MainCharObj2[0]->CharID != Characters_MechTails && MainCharObj2[0]->CharID != Characters_MechEggman)
		DeleteObject_(a1);
	else {
		ObjectFunc(origin, BrokenDownSmoke_t->Target());
		origin(a1);
	}
}

void MetalBox_r(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (GetCollidingPlayer(obj) && isMilesAttackingBox() && data->NextAction < 1)
	{
		data->Collision->CollisionArray->push |= 0x4000u;
		data->field_6 = 1;
		AddScore(20);
		Play3DSound_Pos(4113, &data->Position, 1, 127, 80);
		data->NextAction = 1;
	}

	ObjectFunc(origin, MetalBox_t->Target());
	origin(obj);
}

void MetalBoxGravity_r(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (GetCollidingPlayer(obj) && isMilesAttackingBox() && data->NextAction < 1)
	{
		data->Collision->CollisionArray->push |= 0x4000u;
		data->field_6 = 1;
		AddScore(20);
		Play3DSound_Pos(4113, &data->Position, 1, 127, 80);
		data->NextAction = 1;
	}

	ObjectFunc(origin, MetalBoxGravity_t->Target());
	origin(obj);
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

bool isSuperForm() {
	if (MainCharObj2[0]->CharID == Characters_Tails && MainCharObj2[0]->Upgrades & Upgrades_SuperSonic || CurrentLevel == LevelIDs_FinalHazard)
	{
		return true;
	}

	return false;
}

void Init_MilesActions() {
	if (isMechRemoved)
		WriteCall((void*)0x43D6CD, ForceMiles);

	if (isRando())
		return;

	CheckBreakObject_t = new Trampoline((int)CheckBreakObject, (int)CheckBreakObject + 0x7, CheckBreakObject_r);
	MysticMelody_t = new Trampoline((int)0x6E76A0, (int)0x6E76A0 + 0x6, PlayMysticMelody);
	Dynamite_t = new Trampoline((int)Dynamite_Main, (int)Dynamite_Main + 0x5, CheckBreakDynamite);
	DynamiteHiddenBase_t = new Trampoline((int)DynamiteHiddenBase_Main, (int)DynamiteHiddenBase_Main + 0x5, CheckBreakDynamiteHiddenBase);
	DynamiteSandOcean_t = new Trampoline((int)DynamiteSandOcean_Main, (int)DynamiteSandOcean_Main + 0x6, CheckBreakDynamiteSandOcean);
	PrisonLaneDoor_t = new Trampoline((int)PrisonLaneDoor, (int)PrisonLaneDoor + 0x6, CheckPrisonLaneDoor);
	PrisonLaneDoor4_t = new Trampoline((int)PrisonLaneDoor4, (int)PrisonLaneDoor4 + 0x6, CheckPrisonLaneDoor4);

	SuperAura_t = new Trampoline((int)Super_Something, (int)Super_Something + 0x7, Super_Aura_r);

	DoorIG_t = new Trampoline((int)DoorIG, (int)DoorIG + 0x6, doorIG_r);
	DoorIG2_t = new Trampoline((int)DoorIG2, (int)DoorIG2 + 0x6, doorIG2_r);
	RocketIG_t = new Trampoline((int)RocketIG, (int)RocketIG + 0x6, rocketIG_r);

	BrokenDownSmoke_t = new Trampoline((int)BrokenDownSmokeExec, (int)BrokenDownSmokeExec + 0x7, BrokenDownSmoke_r);

	MetalBox_t = new Trampoline((int)MetalBox, (int)MetalBox + 0x6, MetalBox_r);
	MetalBoxGravity_t = new Trampoline((int)MetalBoxGravity, (int)MetalBoxGravity + 0x6, MetalBoxGravity_r);

	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x776D1E), CheckGravitySwitch);

	//WriteJump(reinterpret_cast<void*>(0x473219), FixJump);

	WriteData<5>((void*)0x6d6324, 0x90); //fix rocket damage
	WriteData<3>((int*)0x751d70, 0x90); //Remove path action, we will manually call it (fix RH last loop)

	WriteData<2>((int*)0x4cd255, 0x90); //remove chara sonic check in cannon core (fix softlock after the first rail)

	//EE Power suply
	WriteData<5>((void*)0x7899e8, 0x90); //remove powersupply

	if (isMilesAdventure) {
		//FinalHazard Stuff
		WriteData<40>((int*)0x498a9d, 0x90); //Remove the game calling super shadow and stuff since we will manually do it.
		WriteCall((void*)0x498a98, LoadSuperFormFinalBattle); //hook "LoadSuperSonic"
		WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely
		WriteData<7>((int*)0x49cfc3, 0x90); //Remove super aura math thing for Tails.
	}
}