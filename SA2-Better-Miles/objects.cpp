#include "pch.h"

static Trampoline* CheckBreakObject_t = nullptr;
static Trampoline* MysticMelody_t = nullptr;
static Trampoline* Dynamite_t = nullptr;
static Trampoline* DynamiteHiddenBase_t = nullptr;
static Trampoline* DynamiteSandOcean_t = nullptr;
static Trampoline* PrisonLaneDoor_t = nullptr;
static Trampoline* PrisonLaneDoor4_t = nullptr;
static Trampoline* SuperAura_t = nullptr;
static Trampoline* DoorIG_t = nullptr;
static Trampoline* DoorIG2_t = nullptr;
static Trampoline* RocketIG_t = nullptr;
static Trampoline* BrokenDownSmoke_t = nullptr;
static Trampoline* MetalBox_t = nullptr;
static Trampoline* MetalBoxGravity_t = nullptr;
static Trampoline* IronBoxEggman_t = nullptr;
static Trampoline* DeleteLevelStuff_t = nullptr;
static Trampoline* Turtle_Function_t = nullptr;
static Trampoline* PowerSupply_event_t = nullptr;
static Trampoline* sub_6129C0_t = nullptr;

void __cdecl PowerSupply_EventTask(ObjectMaster* a1)
{
	if (CurrentCharacter != Characters_MechEggman && CurrentCharacter != Characters_MechTails)
	{
		DeleteObject_(a1);
		return;
	}

	ObjectFunc(origin, PowerSupply_event_t->Target());
	origin(a1);
}

void PatchTurtleAnimation()
{
	if (CurrentLevel != LevelIDs_DryLagoon)
		return;

	if (CurrentCharacter != Characters_Knuckles && CurrentCharacter != Characters_Rouge)
	{
		WriteData<1>((int*)0x642c98, 0x0);
	}
	else
	{
		WriteData<1>((int*)0x642c98, 0xD7);
	}
}

void Turtle_Function_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	if (isMiles()) {

		if (data->Action == 5) {

			if (MilesCO2Extern) {

				char pnum = MilesCO2Extern->base.PlayerNum;

				if (MainCharObj2[pnum])
				{
					if (((MainCharObj1[pnum]->Status & 1) != 0) && (MainCharObj2[pnum]->CurrentDyncolTask != nullptr))
					{

						if (MainCharObj2[pnum]->CurrentDyncolTask->Data1.Entity->field_2 == 25) {

							if (Action_Pressed[pnum])
								MainCharObj1[pnum]->Action = 86;
						}
					}
				}
			}
		}
	}

	ObjectFunc(origin, Turtle_Function_t->Target());
	origin(obj);
}

Bool __cdecl CheckBreakObject_r(ObjectMaster* obj, ObjectMaster* other)
{
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
	if (MilesCO2Extern) {
		CharObj2Base* co2 = &MilesCO2Extern->base;
		EntityData1* data = MainCharObj1[co2->PlayerNum];

		if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, 15))
		{
			if (data->NextAction == 0 && co2->CharID == Characters_Tails) {
				if (Controllers[co2->PlayerNum].on & (Buttons_X | Buttons_B) && (data->Action == 0 || data->Action == 60))
					SetMysticMelodyAction(co2, data);
			}
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


static const void* const loc_6109eb = (void*)0x6109eb;
static const void* const loc_610b62 = (void*)0x610b62;
__declspec(naked) void  KBB_DamageChk() {
	if ( (CurrentCharacter == Characters_Knuckles || CurrentCharacter == Characters_Rouge)
		&& (MainCharObj1[0]->Action == Action_DigFinish || MainCharObj1[0]->Action == Action_DigFinishOnWall)
		|| isAttackingKBB() )
	{
		_asm jmp loc_6109eb
	}
	else {
		_asm jmp loc_610b62
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
			data->Timer = 0;
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

		if (!isMiles())
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

	if (!isMiles())
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

	if (GetCollidingPlayer(obj) && isMilesAttacking() && data->Action == 5)
	{
		data->Action = 6;
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

void breaBoxCheck(EntityData1* data)
{

	if (data)
	{
		if (data->Collision) {

			if (data->Collision->CollidingObject) {

				char pnum = GetPlayerNumber(data->Collision->CollidingObject->Object);

				if (isMilesAttackingBox() && data->NextAction < 1) {
					data->Collision->CollisionArray->push |= 0x4000u;
					data->Timer = 1;
					AddScore(20);
					Play3DSound_Pos(4113, &data->Position, 1, 127, 80);
					data->NextAction = 1;
				}
			}
		}
	}

}
void MetalBox_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	breaBoxCheck(data);

	ObjectFunc(origin, MetalBox_t->Target());
	origin(obj);
}

void MetalBoxGravity_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	breaBoxCheck(data);

	ObjectFunc(origin, MetalBoxGravity_t->Target());
	origin(obj);
}

void IronBoxEggman_r(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;

	breaBoxCheck(data);

	ObjectFunc(origin, IronBoxEggman_t->Target());
	origin(obj);
}

void DeleteLevelStuff_r() {

	DeleteLevelStuff();
	FreeAllCustomSounds();
	Delete_Tornado();
	Delete_TornadoTransform();
}

ObjectMaster* __cdecl sub_6129C0(ObjectMaster* a1)
{
	EntityData1* data = a1->Data1.Entity;
	
	FunctionPointer(ObjectMaster*, origin, (ObjectMaster * a1), sub_6129C0_t->Target());
	ObjectMaster* obj = origin(a1);

	data->Action = data->Action;
	return obj;
}



void Init_ObjectsHacks() {

	if (isRando())
		return;

	WriteCall((void*)0x43B364, DeleteLevelStuff_r);

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
	PowerSupply_event_t = new Trampoline((int)0x78A450, (int)0x78A455, PowerSupply_EventTask);
	WriteJump(reinterpret_cast<void*>(0x776D1E), CheckGravitySwitch);
	WriteJump(reinterpret_cast<void*>(0x776330), CheckBreakCGGlasses);	

	//KingBoomBoo
	WriteJump(reinterpret_cast<void*>(0x6109d5), KBB_DamageChk);
	WriteData<17>((int*)0x6109da, 0x90); //need 5 bytes to jump so we nop the rest and will add this code manually

	WriteData<5>((void*)0x6d6324, 0x90); //fix rocket damage
	WriteData<3>((int*)0x751d70, 0x90); //Remove path action, we will manually call it (fix RH last loop)
	WriteData<2>((int*)0x4cd255, 0x90); //remove chara sonic check in cannon core (fix softlock after the first rail)

	Turtle_Function_t = new Trampoline((int)0x642B10, (int)0x642B16, Turtle_Function_r);
	IronBoxEggman_t = new Trampoline((int)0x6FBC20, (int)0x6FBC26, IronBoxEggman_r);

	sub_6129C0_t = new Trampoline((int)0x6129C0, (int)0x6129C6, sub_6129C0);

	/*if (isMilesAdventure) {
		//FinalHazard Stuff
		WriteData<40>((int*)0x498a9d, 0x90); //Remove the game calling super shadow and stuff since we will manually do it.
		WriteCall((void*)0x498a98, LoadSuperFormFinalBattle); //hook "LoadSuperSonic"
		WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely
		WriteData<7>((int*)0x49cfc3, 0x90); //Remove super aura math thing for Tails.
	}*/
}