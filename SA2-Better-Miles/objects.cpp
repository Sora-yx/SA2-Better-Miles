#include "pch.h"

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

void CheckAndSetHackObject(CharObj2Base* co2) {
	if (co2->CharID == Characters_MechTails || co2->CharID == Characters_MechEggman) {
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
	MainCharacter[0]->DisplaySub_Delayed3 = Super_Something;
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

	//SuperAura_t = new Trampoline((int)Super_Something, (int)Super_Something + 0x7, Super_Aura_r);

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

	/*if (isMilesAdventure) {
		//FinalHazard Stuff
		WriteData<40>((int*)0x498a9d, 0x90); //Remove the game calling super shadow and stuff since we will manually do it.
		WriteCall((void*)0x498a98, LoadSuperFormFinalBattle); //hook "LoadSuperSonic"
		WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely
		WriteData<7>((int*)0x49cfc3, 0x90); //Remove super aura math thing for Tails.
	}*/
}