#include "stdafx.h"

Trampoline* CheckBreakObject_t;
Trampoline* MysticMelody_t;
Trampoline* Dynamite_t;
Trampoline* DynamiteHiddenBase_t;
Trampoline* PrisonLaneDoor_t;
Trampoline* PrisonLaneDoor4_t;
Trampoline* SuperAura_t;
Trampoline* DoorIG_t;
Trampoline* DoorIG2_t;
Trampoline* RocketIG_t;


static const void* const GetAnalogPtr2 = (void*)0x45A870;
inline int GetAnalogASM2(EntityData1* data, CharObj2Base* co2, Angle* angle, Float* magnitude)
{

	int result;
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


static const void* const PGetAccelPtr = (void*)0x460860;
static inline void PGetAcceleration(EntityData1* a1, CharObj2Base* co2, EntityData2_* data2)
{
	__asm
	{
		push[data2] // a3
		mov ebx, co2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call PGetAccelPtr

		add esp, 4 // a3
	}
}


static const void* const sub_4616E0Ptr = (void*)0x4616E0;
static inline void sub_4616E0(EntityData1* a1, EntityData2_* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		push a2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call sub_4616E0Ptr
		add esp, 8 // a2
	}
}



static const void* const sub_469050Ptr = (void*)0x469050;
static inline void sub_469050(EntityData1* a1, EntityData2_* a2, CharObj2Base* a3)
{
	__asm
	{
		push[a3] // a3
		mov ebx, a2 // a2
		mov eax, a1 // a1

		// Call your __cdecl function here:
		call sub_469050Ptr
		add esp, 4 // a2
	}
}


void PlayerMoveStuff(EntityData1* a1, EntityData2_* a2, CharObj2Base* a3) {
	PGetAcceleration(a1, a3, a2);
	sub_4616E0(a1, a2, a3);
	sub_469050(a1, a2, a3);
	return;
}


static const void* const VibeThingPtr = (void*)0x438E70;
static void __declspec(naked) VibeThingASM(int a1, signed int a2, int a3, signed int a4)
{
	__asm
	{
		push[esp + 04h] // int a4
		push ecx // a3
		push edx // int a2
		push eax // a1

		// Call your __cdecl function here:
		call VibeThingPtr

		pop eax // a1
		pop edx // int a2
		pop ecx // a3
		add esp, 4 // int a4
		retn
	}
}

void CallVibeThing(int a1, signed int a2, int a3, signed int a4)
{
	VibeThingASM(a1, a2, a3, a4);
	return;
}


bool isMilesAttacking() {

	if (MainCharObj2[0]->CharID != Characters_Tails)
		return false;

	EntityData1* data1 = MainCharObj1[0];

	if (data1->Action == Flying || data1->Action == Jumping || data1->Action == Spinning || data1->Action == Rolling)
		return true;

	return false;
}


Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];


	if (isMilesAttacking() && GetCollidingPlayer(obj))
		return 1;

	FunctionPointer(Bool, original, (ObjectMaster* obj, ObjectMaster* other), CheckBreakObject_t->Target());
	return original(obj, other);
}


static const void* const loc_776339 = (void*)0x776339;
__declspec(naked) void  CheckBreakCGGlasses() {

	if (MainCharObj1[0]->Action == 13 || isMilesAttacking())
	{
		_asm jmp loc_776339
	}
}


static const void* const loc_6d6934 = (void*)0x6d6934;
__declspec(naked) void  CheckBreakIronBox() {

	if (MainCharObj2[0]->CharID == Characters_Tails || MainCharObj2[0]->Upgrades & Upgrades_SonicFlameRing != 0)
	{
		_asm jmp loc_6d6934
	}
}


static const void* const loc_46ee89 = (void*)0x46ee89;
static const void* const loc_46ee9b = (void*)0x46ee9b;
__declspec(naked) void CheckUpgradeBox() {

	if (MainCharObj2[0]->CharID == Characters_Rouge && (MainCharObj2[0]->Upgrades & Upgrades_RougeIronBoots) != 0 || (isMilesAttacking() && MainCharObj2[0]->CharID == Characters_Tails)) {
		_asm jmp loc_46ee89
	}
	else {
		_asm jmp loc_46ee9b
	}
}

static void __declspec(naked) sub_46EE00()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call CheckUpgradeBox

		add esp, 4 // a1<eax> is also used for return value
		retn
	}
}

static const void* const sub_475F00ptr = (void*)0x475F00;
static void __declspec(naked) SetMysticMelodyAction(CharObj2Base* a1, EntityData1* a2)
{
	__asm
	{
		push ecx // a2
		push eax // a1

		// Call your __cdecl function here:
		call  sub_475F00ptr

		pop eax // a1
		pop ecx // a2
		retn
	}
}

int __cdecl IsPlayerInsideSphere(NJS_VECTOR* x_1, float radius)
{
	float v2; // edx
	float v3; // eax
	int v4; // esi
	EntityData1* v5; // eax
	CollisionInfo* v6; // eax
	float* v7; // eax
	double v8; // st7
	float v10; // [esp+4h] [ebp-14h]
	float v11; // [esp+8h] [ebp-10h]
	NJS_VECTOR v; // [esp+Ch] [ebp-Ch] BYREF
	float v13; // [esp+1Ch] [ebp+4h]

	v2 = x_1->y;
	v3 = x_1->z;
	v13 = x_1->x;
	v10 = v2;
	v11 = v3;
	v4 = 0;
	while (1)
	{
		v5 = MainCharObj1[v4];
		if (v5)
		{
			v6 = v5->Collision;
			if (v6)
			{
				v7 = (float*)&v6->CollisionArray->center;
				v8 = v7[2];
				// pointer to Y of the first vector because sega hates everything
				v7 += 3;
				v.x = v8 - v13;
				v.y = *v7 - v10;
				v.z = v7[1] - v11;
				if (njScalor(&v) - radius < 0.0)
				{
					break;
				}
			}
		}
		if (++v4 >= 2)
		{
			return 0;
		}
	}
	return v4 + 1;
}

EntityData2_* PlayMysticMelody(ObjectMaster* obj)
{
	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data = MainCharObj1[0];

	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 30))
	{
		if (Controllers[co2->PlayerNum].on & (Buttons_X | Buttons_B))
			SetMysticMelodyAction(co2, data);
	}

	ObjectFunc(origin, MysticMelody_t->Target());
	origin(obj);
}


static const void* const loc_776D2A = (void*)0x776d23;
__declspec(naked) void  CheckGravitySwitch() {

	if (MainCharObj1[0]->Action == 0x53 || isMilesAttacking())
	{
		_asm jmp loc_776D2A
	}
}

void ForceMiles(int player) {
	if (!TwoPlayerMode) {
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

void CheckAndSetBreakDoor() {

	if (CurrentCharacter == Characters_Tails || MainCharObj2[0]->CharID == Characters_Tails) {
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
	}
	else { //restore original values
		WriteData<1>((int*)0x715b58, 0x6);
		WriteData<1>((int*)0x715aa8, 0x6);
		WriteData<1>((int*)0x7158bf, 0x6);

		WriteData<1>((int*)0x79b427, 0x6);
		WriteData<1>((int*)0x79b959, 0x6);
		WriteData<1>((int*)0x79be57, 0x6);
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
	//MysticMelody_t = new Trampoline((int)0x6E76A0, (int)0x6E76A0 + 0x6, PlayMysticMelody);
	Dynamite_t = new Trampoline((int)Dynamite_Main, (int)Dynamite_Main + 0x5, CheckBreakDynamite);
	DynamiteHiddenBase_t = new Trampoline((int)DynamiteHiddenBase_Main, (int)DynamiteHiddenBase_Main + 0x5, CheckBreakDynamiteHiddenBase);
	PrisonLaneDoor_t = new Trampoline((int)PrisonLaneDoor, (int)PrisonLaneDoor + 0x6, CheckPrisonLaneDoor);
	PrisonLaneDoor4_t = new Trampoline((int)PrisonLaneDoor4, (int)PrisonLaneDoor4 + 0x6, CheckPrisonLaneDoor4);

	SuperAura_t = new Trampoline((int)Super_Something, (int)Super_Something + 0x7, Super_Aura_r);
	
	DoorIG_t = new Trampoline((int)DoorIG, (int)DoorIG + 0x6, doorIG_r);
	DoorIG2_t = new Trampoline((int)DoorIG2, (int)DoorIG2 + 0x6, doorIG2_r);
	RocketIG_t = new Trampoline((int)RocketIG, (int)RocketIG + 0x6, rocketIG_r);


	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteJump(reinterpret_cast<void*>(0x6d6911), CheckBreakIronBox);	
    WriteJump(reinterpret_cast<void*>(0x46ee7c), CheckUpgradeBox);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);
	WriteData<1>((int*)0x776D20, 0x0); //CG Gravity switch need to be updated

	WriteData<5>((void*)0x6d6324, 0x90); //fix rocket damage

	//FinalHazard Stuff
	WriteData<40>((int*)0x498a9d, 0x90); //Remove the game calling super shadow and stuff since we will manually do it.
	WriteCall((void*)0x498a98, LoadSuperFormFinalBattle); //hook "LoadSuperSonic"
	WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely	
	WriteData<7>((int*)0x49cfc3, 0x90); //Remove super aura math thing for Tails.

	//EE Power suply
	WriteData<5>((void*)0x7899e8, 0x90); //remove powersupply
}