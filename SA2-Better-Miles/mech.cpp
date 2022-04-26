#include "pch.h"
#include "tornado.h"

NJS_VECTOR SavePos = { 0, 0, 0 };

ModelInfo* TornadoTransfo = nullptr;
AnimationFile* TornadoTransfoMotion = nullptr;

NJS_TEXNAME tornadoTransfoTex[150];
NJS_TEXLIST tornadoTransfoTexList = { arrayptrandlength(tornadoTransfoTex) };

Trampoline* MechTails_runsActions_t = nullptr;
Trampoline* sub_75DF80_t = nullptr;
Trampoline* CCL_CalcColli_t = nullptr;

bool isInMech = false;

CollisionData SuperLaserCol = { 0, CollisionShape_Cyl1, 7, 0xE1, 0x800400, {0}, 5.0, 40.0, 30.0, 30.0, {0, 0, 0x0 } };


void SoundEffect_Tornado(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	switch (data->Action)
	{
	case 0:
	{
		PlayCustomSoundVolume(SE_tornado_Transfo01, 1);
		data->Action++;
		break;
	case 1:
		if (++data->Timer == 60)
		{
			PlayCustomSoundVolume(SE_tornado_Transfo02, 1);
			data->Action++;
			data->Timer = 0;

		}
		break;
	case 2:
		if (++data->field_2 == 60)
		{
			PlayCustomSoundVolume(SE_tornado_Transfo03, 1);
			data->Action++;
		}
		break;
	default:
		DeleteObject_(obj);
		break;

	}
	}
}

void DeleteAndLoadMech(char pNum) {

	DeleteObject_(MainCharacter[pNum]);
	CurrentCharacter = Characters_MechTails;
	LoadMechTails(pNum);
	InitCharacterSound();
	return;
}

void DeleteAndLoadMiles(char pNum) {

	DeleteObject_(MainCharacter[pNum]);
	CurrentCharacter = Characters_Tails;
	LoadTails(pNum);
	InitCharacterSound();
	return;
}

void DeleteMech(ObjectMaster* obj)
{
	isTransform = false;
	isInMech = false;
}

void UnTransfoMech_Display(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	float frame = TornadoTransfoMotion->getmotion()->nbFrame;
	NJS_OBJECT* tornadoMDL = TornadoTransfo->getmodel();
	NJS_MOTION* TornadoMotion = TornadoTransfoMotion->getmotion();
	EntityData1* player = MainCharObj1[data->Index];

	njSetTexture(&tornadoTransfoTexList);
	njPushMatrixEx();

	njTranslateV(0, &player->Position);
	njRotateX(0, player->Rotation.x);
	njRotateY(0, 0x8000 - player->Rotation.y);
	njRotateZ(0, player->Rotation.z);

	if (data->Action == 2)
		DrawMotionAndObject(TornadoMotion, tornadoMDL, data->Scale.z);
	else if (data->Action < 2)
		DrawMotionAndObject(TornadoMotion, tornadoMDL, 199);

	njPopMatrixEx();
}

void Untransform_Mech(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];
	float frame = TornadoTransfoMotion->getmotion()->nbFrame;

	switch (data->Action)
	{
	case 0:
	{
		playerData->Action = ObjectControl;
		LoadChildObject(LoadObj_Data1, SoundEffect_Tornado, obj);
		DrawSubtitles(1, "\a Tornado, transformation!", 120, 1);
		playerData->Rotation.x = 0;
		playerData->Rotation.z = 0;
		data->Rotation.y = playerData->Rotation.y;
		PlayVoice(2, 2433);
		ControllerEnabled[pNum] = 0;

		obj->DeleteSub = DeleteMech;
		playerData->Position.y += 1;
		SavePos = playerData->Position;
		SavePos.y += 5;
		isTransform = true;
		co2->Powerups |= Powerups_Invincibility;
		co2->Speed = { 0, 0, 0 };
		SetCameraFacePlayer(pNum, playerData, 40.0f);
		data->Scale.z = frame;
		obj->DisplaySub = UnTransfoMech_Display;
		DeleteAndLoadMiles(pNum);
		playerData->Action = ObjectControl;
		co2->AnimInfo.Next = 35;
		data->Action++;
	}
	break;
	case 1:
		playerData->Action = ObjectControl;
		playerData->Position = SavePos;
		playerData->Rotation.y = data->Rotation.y;

		if (++data->Timer == 20)
		{
			co2->AnimInfo.Next = 35;
			playerData->Position.y += 5;
			data->Action++;
			data->Timer = 0;
		}
		break;
	case 2:

		CamEventAngleY += 320;
		data->Scale.z--;
		if (data->Scale.z <= 0)
		{
			PlayCustomSoundVolume(SE_tornadoTransfoFinish, 2);
			isInMech = true;
			ObjectMaster* tornado = LoadObject(2, "Tornado", Tornado_Main, LoadObj_Data1);
			tornado->Data1.Entity->Index = co2->PlayerNum;
			ResetCam(CameraData.gap1AC[168], 0);
			isTransform = false;
			co2->Powerups &= Powerups_Invincibility;
			ControllerEnabled[pNum] = 1;
			data->Action++;
			data->Scale.z = 0;
		}
		break;
	default:
		if (++data->Timer == 40)
		{
			DeleteObject_(obj);
		}
		return;
	}
}

void UntransfoMech_CheckInput(CharObj2Base* co2, EntityData1* playerData) {

	if (GameState != GameStates_Ingame || !co2 || !isInMech)
		return;

	if (playerData->Action <= Action_Run) {

		if (Controllers[co2->PlayerNum].press & Buttons_Down)
		{
			ObjectMaster* tornado = LoadObject(2, "MechUntransfo", Untransform_Mech, LoadObj_Data1);
			tornado->Data1.Entity->Index = co2->PlayerNum;
			return;
		}
	}
}


void TransfoMech_Display(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	float frame = TornadoTransfoMotion->getmotion()->nbFrame;
	NJS_OBJECT* tornadoMDL = TornadoTransfo->getmodel();
	NJS_MOTION* TornadoMotion = TornadoTransfoMotion->getmotion();
	EntityData1* player = MainCharObj1[data->Index];


	njSetTexture(&tornadoTransfoTexList);
	njPushMatrixEx();

	njTranslateV(0, &player->Position);
	njRotateX(0, player->Rotation.x);
	njRotateY(0, 0x8000 - player->Rotation.y);
	njRotateZ(0, player->Rotation.z);


	if (data->Action == 2)
		DrawMotionAndObject(TornadoMotion, tornadoMDL, data->Scale.z);
	else if (data->Action == 3)
		DrawMotionAndObject(TornadoMotion, tornadoMDL, frame - 1);
	else if (data->Action < 4)
		DrawObject(tornadoMDL);


	njPopMatrixEx();
}

void CallMech(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];
	float frame = TornadoTransfoMotion->getmotion()->nbFrame;

	switch (data->Action)
	{
	case 0:
	{
		obj->DeleteSub = DeleteMech;
		isTransform = true;
		isInMech = true;
		co2->Powerups |= Powerups_Invincibility;
		co2->Speed = { 0, 0, 0 };
		SetCameraFacePlayer(pNum, playerData, 40.0f);
		data->Scale.z = 0;
		StopMusic();
		PlayJingle("tornado2.adx");
		PlayVoice(2, 2433);
		DrawSubtitles(1, "\a Tornado, transformation!", 120, 1);
		obj->DisplaySub = TransfoMech_Display;
		playerData->Rotation.x = 0;
		playerData->Rotation.z = 0;
		SavePos = playerData->Position;
		data->Rotation.y = playerData->Rotation.y;

		data->Action++;
	}
	break;
	case 1:

		if (++data->Timer == 15)
		{
			LoadChildObject(LoadObj_Data1, SoundEffect_Tornado, obj);
			data->Action++;
			data->Timer = 0;
		}
		break;
	case 2:

		CamEventAngleY += 320;
		data->Scale.z++;

		if (data->Scale.z >= frame)
		{
			ResetCam(CameraData.gap1AC[168], 0);
			data->Action++;
			data->Scale.z = 0;
		}
		break;
	case 3:
		data->Timer = 0;
		DeleteAndLoadMech(pNum);
		playerData = MainCharObj1[pNum];
		playerData->Position = SavePos;
		data->Action++;
		break;
	case 4:
		playerData->Position = SavePos;
		playerData->Rotation.y = data->Rotation.y;
		if (++data->Timer == 7)
		{
			PlayCustomSoundVolume(SE_tornadoTransfoFinish, 2);
			isTransform = false;
			co2->Powerups &= Powerups_Invincibility;
			int rng = rand() % 2 ? 1695 : 2274;
			PlayVoice(2, 2274);
			DrawSubtitles(1, "\a I'll show you how powerful my Cyclone is!", 150, 1);
			ControllerEnabled[pNum] = 1;
			data->Action++;
		}
		break;
	default:
		DeleteObject_(obj);
		return;
	}
}

void ResetSoundSystem_r() {

	if (isTransform && GameState == GameStates_Ingame)
		return;

	ResetSoundSystem();
	return;
}


void sub_75DF80_r(ObjectMaster* obj)
{
	if (isTransform)
		return;

	TARGET_DYNAMIC(sub_75DF80);
}

unsigned int __cdecl CCL_CalcColli_r(ObjectMaster* a1, int* a2) //fix crash when deleting player
{

	if (a1->MainSub == nullptr || !a2 || a2 + 52 == nullptr || isTransform)
		return 0;


	TARGET_DYNAMIC(CCL_CalcColli)(a1, a2);
}

void Tails_SuperAttack_CheckInput(CharObj2Base* co2, EntityData1* data, EntityData2* data2, MechEggmanCharObj2* tailsCO2) {

	if (GameState != GameStates_Ingame || !co2)
		return;

	if (data->Action <= Action_Run) {

		if (Controllers[co2->PlayerNum].press & Buttons_Y)
		{
			TailsEggman_LaserAttack(co2, data, data2, tailsCO2);
			return;
		}
	}
}

void Load_TornadoTransfo_ModelsTextures() {
	TornadoTransfo = LoadMDL("tornadoTransfoMDL", ModelFormat_Chunk);
	TornadoTransfoMotion = LoadAnim("TornadoTransfo");
	LoadTextureList("tornadoTransfoTex", &tornadoTransfoTexList);
	return;
}

void __cdecl MechTails_runsActions_r(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, MechEggmanCharObj2* co2Miles) {

	FunctionPointer(void, original, (EntityData1 * data1, EntityData2 * data2, CharObj2Base * co2, MechEggmanCharObj2 * co2Miles), MechTails_runsActions_t->Target());
	original(data1, data2, co2, co2Miles);


	if (!TwoPlayerMode && co2)
	{
		if (!data1->Action && !isInMech)
		{
			isInMech = true;
		}

		if (co2->CharID2 == Characters_MechTails && !isBossLevel()) {

			UntransfoMech_CheckInput(co2, data1);

			if ((TimerSeconds > 0 || TimerMinutes > 0)) {
				WriteData<1>((int*)0x749E90, 0xF8); //remove laser delay lol
				Tails_SuperAttack_CheckInput(co2, data1, data2, co2Miles);
			}
		}
	}
}

void SuperLaserCol_Hack(ObjectMaster* obj, CollisionData* collision, int count, unsigned __int8 a4) {

	if (TwoPlayerMode || isBossLevel())
	{
		InitCollision(obj, collision, count, a4); //let the original code handle it
		return;
	}

	InitCollision(obj, &SuperLaserCol, count, 1); //change the collision so we can hurt enemies.
	EntityData1* data1 = obj->Data1.Entity;
	data1->Collision->CollisionArray->attr |= 0x40000u;
	data1->Collision->Flag &= 0xFFBFu;
	data1->Collision->Range += 500.0f;
	data1->Collision->CollisionArray->param3 = 120.0f;

}


static void __declspec(naked) SuperLaserColHack_ASM()
{
	__asm
	{
		push[esp + 0Ch] // __int8 a4
		push[esp + 0Ch] // count
		push[esp + 0Ch] // collision
		push eax // obj
		call SuperLaserCol_Hack
		add esp, 4
		add esp, 4
		add esp, 4
		add esp, 4
		retn
	}
}

void Delete_TornadoTransform() {
	FreeMDL(TornadoTransfo);
	TornadoTransfo = nullptr;
	FreeTexList(&tornadoTransfoTexList);
	FreeAnim(TornadoTransfoMotion);
	TornadoTransfoMotion = nullptr;
	isInMech = false;
	WriteData<1>((int*)0x749E90, 0xFF); //restore laser delay
	return;
}


void Init_TailsMechHack() {
	MechTails_runsActions_t = new Trampoline(0x742C10, 0x742C17, MechTails_runsActions_r);
	WriteCall((void*)0x438C23, ResetSoundSystem_r); //fix an issue where stage sound effect are unload when swapping Character.
	sub_75DF80_t = new Trampoline(0x75DF80, 0x75DF86, sub_75DF80_r); //fix nonsense crash 
	CCL_CalcColli_t = new Trampoline((int)CCL_CalcColli, (int)CCL_CalcColli + 0x6, CCL_CalcColli_r);
	WriteCall((void*)0x7607E2, SuperLaserColHack_ASM);
	return;
}

