#include "pch.h"
#include "tornado.h"

NJS_VECTOR SavePos = { 0, 0, 0 };

ModelInfo* TornadoTransfo = nullptr;
AnimationFile* TornadoTransfoMotion = nullptr;

NJS_TEXNAME tornadoTransfoTex[150];
NJS_TEXLIST tornadoTransfoTexList = { arrayptrandlength(tornadoTransfoTex) };

Trampoline* MechTails_main_t;
Trampoline* MechTails_runsActions_t;

bool isInMech = false;

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
		if (++data->field_6 == 60)
		{
			PlayCustomSoundVolume(SE_tornado_Transfo02, 1);
			data->Action++;
			data->field_6 = 0;

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
		LoadChildObject(LoadObj_Data1, SoundEffect_Tornado, obj);
		displayText(1, "\a Tornado, transformation!", 120, 1);
		playerData->Rotation.x = 0;
		playerData->Rotation.z = 0;
		data->Rotation.y = playerData->Rotation.y;
		PlayVoice(2, 2433);
		ControllerEnabled[pNum] = 0;
		playerData->Action = ObjectControl;
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

		if (++data->field_6 == 20)
		{
			co2->AnimInfo.Next = 35;
			playerData->Position.y += 5;
			data->Action++;
			data->field_6 = 0;
		}
		break;
	case 2:

		CamAngleY += 320;
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
		if (++data->field_6 == 40)
		{
			DeleteObject_(obj);
		}
		return;
	}
}

void UntransfoMech_CheckInput(CharObj2Base* co2, EntityData1* data) {

	if (GameState != GameStates_Ingame || !co2 || !isInMech)
		return;

	if (Controllers[co2->PlayerNum].press & Buttons_Down)
	{
		ObjectMaster* tornado = LoadObject(2, "MechUntransfo", Untransform_Mech, LoadObj_Data1);
		tornado->Data1.Entity->Index = co2->PlayerNum;
		data->Action++;
		return;
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
		PlayJingle("tornado2.adx");
		PlayVoice(2, 2433);
		displayText(1, "\a Tornado, transformation!", 120, 1);
		obj->DisplaySub = TransfoMech_Display;
		playerData->Rotation.x = 0;
		playerData->Rotation.z = 0;
		SavePos = playerData->Position;
		data->Rotation.y = playerData->Rotation.y;

		data->Action++;
	}
	break;
	case 1:

		if (++data->field_6 == 15)
		{
			LoadChildObject(LoadObj_Data1, SoundEffect_Tornado, obj);
			data->Action++;
			data->field_6 = 0;
		}
		break;
	case 2:

		CamAngleY += 320;
		data->Scale.z++;

		if (data->Scale.z >= frame)
		{
			ResetCam(CameraData.gap1AC[168], 0);
			data->Action++;
			data->Scale.z = 0;
		}
		break;
	case 3:
		data->field_6 = 0;
		DeleteAndLoadMech(pNum);
		InitCharacterSound();

		playerData = MainCharObj1[pNum];
		playerData->Position = SavePos;
		data->Action++;
		break;
	case 4:
		playerData->Position = SavePos;
		playerData->Rotation.y = data->Rotation.y;
		if (++data->field_6 == 7)
		{
			PlayCustomSoundVolume(SE_tornadoTransfoFinish, 2);
			isTransform = false;
			co2->Powerups &= Powerups_Invincibility;
			int rng = rand() % 2 ? 1695 : 2274;
			PlayVoice(2, 2274);
			displayText(1, "\a I'll show you how powerful my Cyclone is!", 150, 1);
			ControllerEnabled[pNum] = 1;
			data->Action++;
		}
		break;

	case 5:
		UntransfoMech_CheckInput(co2, data);
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


void Load_TornadoTransfo_ModelsTextures() {
	TornadoTransfo = LoadMDL("tornadoTransfoMDL", ModelFormat_Chunk);
	TornadoTransfoMotion = LoadAnim("TornadoTransfo");
	LoadTextureList("tornadoTransfoTex", &tornadoTransfoTexList);
	return;
}

void __cdecl MechTails_runsActions_r(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, MechEggmanCharObj2* co2Miles) {

	FunctionPointer(void, original, (EntityData1 * data1, EntityData2 * data2, CharObj2Base * co2, MechEggmanCharObj2 * co2Miles), MechTails_runsActions_t->Target());
	original(data1, data2, co2, co2Miles);

	Tornado_RunsActions(data1, co2);
}

void __cdecl MechTails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, MechTails_main_t->Target());
	origin(obj);

	CharObj2Base* co2 = obj->Data2.Character;
	EntityData1* data1 = obj->Data1.Entity;
	EntityData2* data2 = (EntityData2*)obj->EntityData2;
	//TailsCharObj2* co2Miles = (TailsCharObj2*)obj->Data2.Undefined;
	char pID = co2->PlayerNum;

	Tornado_MainActions(data1, co2, data2);
}

void Init_TailsMechHack() {
	MechTails_main_t = new Trampoline((int)MechEggman_Main, (int)MechEggman_Main + 0x6, MechTails_Main_r);
	MechTails_runsActions_t = new Trampoline(0x742C10, 0x742C17, MechTails_runsActions_r);
	WriteCall((void*)0x438C23, ResetSoundSystem_r); //fix an issue where stage sound effect are unload when swapping Character.
	return;
}