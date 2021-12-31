#include "pch.h"
#include "tornado.h"

NJS_VECTOR SavePos = { 0, 0, 0 };

ModelInfo* TornadoTransfo = nullptr;
AnimationFile* TornadoTransfoMotion = nullptr;

NJS_TEXNAME tornadoTransfoTex[150];
NJS_TEXLIST tornadoTransfoTexList = { arrayptrandlength(tornadoTransfoTex) };

void DeleteAndLoadMech(char pNum) {

	DeleteObject_(MainCharacter[pNum]);
	CurrentCharacter = Characters_MechTails;
	LoadMechTails(pNum);
	InitCharacterSound();
	return;
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


void DeleteMech(ObjectMaster* obj)
{
	isTransform = false;
	isTornadoOn = false;
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
		co2->Powerups |= Powerups_Invincibility;
		co2->Speed = { 0, 0, 0 };
		SetCameraFacePlayer(pNum, playerData, 40.0f);
		data->Scale.z = 0;
		PlayJingle("tornado2.adx");
		PlayVoice(2, 2433);
		obj->DisplaySub = TransfoMech_Display;
		SavePos = playerData->Position;

		data->Action++;
	}
	break;
	case 1:

		if (++data->field_6 == 20)
		{
			data->Action++;
			data->field_6 = 0;
		}
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
		if (++data->field_6 == 7)
		{
			isTransform = false;
			co2->Powerups &= Powerups_Invincibility;
			int rng = rand() % 2 ? 1695 : 2274;
			PlayVoice(2, rng);
			ControllerEnabled[pNum] = 1;
			data->Action++;
		}
		break;
	default:
		DeleteObject_(obj);
		return;

	}
}

void Load_TornadoTransfo_ModelsTextures() {
	TornadoTransfo = LoadMDL("tornadoTransfoMDL", ModelFormat_Chunk);
	TornadoTransfoMotion = LoadAnim("TornadoTransfo");
	LoadTextureList("tornadoTransfoTex", &tornadoTransfoTexList);
	return;
}

void Init_TailsMechHack() {

}