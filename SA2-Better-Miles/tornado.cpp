#include "pch.h"

ModelInfo* Tornado = nullptr;
AnimationFile* TornadoMotion = nullptr;

ModelInfo* TornadoTransfo = nullptr;
AnimationFile* TornadoTransfoMotion = nullptr;

NJS_TEXLIST* tornadoTex;

NJS_TEXNAME tornadoTransfoTex[150];
NJS_TEXLIST tornadoTransfoTexList = { arrayptrandlength(tornadoTransfoTex) };

bool isTornadoOn = false;

enum TornadoE {
	tornadoInit,
	tornadoIntro,
	tornadoTransition,
	tornadoTransition2,
	tornadoTransition3,
	tornadoPlayable,
	tornadoTransfoMech,
	tornadoExit
};

bool isInTornado(char pNum) {

	if (!MainCharObj1[pNum])
		return false;

	return MainCharObj1[pNum]->Action >= TornadoStanding && MainCharObj1[pNum]->Action <= TornadoDescending;
}

void DeleteAndLoadMiles(char pNum) {

	DeleteObject_(MainCharacter[pNum]);
	CurrentCharacter = Characters_Tails;
	LoadTails(pNum);
	InitCharacterSound();
	return;
}

NJS_VECTOR SavePos = { 0, 0, 0 };

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

DataPointer(NJS_VECTOR, CamPosAgain, 0x1DCFE10);
void CallMech(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];
	float frame = TornadoTransfoMotion->getmotion()->nbFrame;
	DWORD a2[2] = { 0.5f, 0.5f };

	switch (data->Action)
	{
	case 0:
	{	
		co2->Speed = { 0, 0, 0 };
		sub_46C6D0(pNum, playerData->Position.x, playerData->Position.y, playerData->Position.z);
		SetCameraEvent(pNum, 24);
		DoSomethingWithCam(*(DWORD*)&CameraData.gap1AC[9432 * pNum + 168], 0, 0);
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
	
			PlayVoice(2, 1695);
			ControllerEnabled[pNum] = 1;
			data->Action++;
		}
		break;
	default:
		DeleteObject_(obj);
		return;

	}
}

void Tornado_Display(ObjectMaster* obj) {

	HMODULE** DLL = datadllhandle;
	EntityData1* data = obj->Data1.Entity;


	if (!DLL)
		return;

	HMODULE dataDll = **DLL;

	if (!dataDll)
		return;

	FARPROC motion_tornado_3rd = GetProcAddress(dataDll, "motion_tornado_3rd");
	NJS_MOTION* TornadoMotion = (NJS_MOTION*)motion_tornado_3rd;

	EntityData1* player = MainCharObj1[data->Index];

	njSetTexture(tornadoTex);
	njPushMatrixEx();

	if (data->Action != tornadoPlayable) {
		njTranslateV(0, &data->Position);
		njRotateY(0, data->Rotation.y);

	}
	else {
		njTranslateV(0, &player->Position);
		njRotateX(0, player->Rotation.x);
		njRotateY(0, 0x8000 - player->Rotation.y);
		njRotateZ(0, player->Rotation.z);
	}


	DrawMotionAndObject(TornadoMotion, Tornado->getmodel(), FrameCountIngame % TornadoMotion->nbFrame);
	njPopMatrixEx();
}

void Mech_CallCheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (GameState != GameStates_Ingame || !co2 || !isTornadoOn)
		return;

	if (Controllers[co2->PlayerNum].on & Buttons_Y && Controllers[co2->PlayerNum].press & Buttons_Left)
	{
		data1->Action = tornadoTransfoMech;
		return;
	}
}


void Tornado_CallCheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (GameState != GameStates_Ingame || !co2 || isTornadoOn)
		return;

	if (Controllers[co2->PlayerNum].on & Buttons_Y && Controllers[co2->PlayerNum].press & Buttons_Right)
	{
		isTornadoOn = true;
		ObjectMaster* tornado = LoadObject(2, "Tornado", Tornado_Main, LoadObj_Data1);
		tornado->Data1.Entity->Index = co2->PlayerNum;

		return;
	}
}

void Tornado_AbortCheckInput(CharObj2Base* co2, EntityData1* playerData) {

	if (GameState != GameStates_Ingame || !co2 || !isTornadoOn)
		return;

	char pNum = co2->PlayerNum;

	if (Controllers[pNum].on & Buttons_Y && Controllers[pNum].press & Buttons_Right && isInTornado(pNum))
	{
		StopMusic();
		ResetMusic();
		isTornadoOn = false;
		co2->Speed.y += 3;
		co2->AnimInfo.Next = 15;
		playerData->Action = Action_Fall;

		return;
	}
}

void Tornado_Main(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;

	EntityData1* player = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	ObjectMaster* mech;

	if (!player)
		return;

	switch (data->Action)
	{
	case tornadoInit:
		ControllerEnabled[pNum] = 0;
		player->Action = 0;
		co2->AnimInfo.Current = 0;

		PlayJingle("tornado.adx");
		obj->DisplaySub = Tornado_Display;
		co2->Powerups |= Powerups_Invincibility;
		player->Rotation = data->Rotation;
		data->Position = player->Position;
		data->Position.x += 220;
		data->Position.y = data->Position.y + 15.0;
		data->Action++;
		break;
	case tornadoIntro:

		LookAt(&data->Position, &player->Position, nullptr, &data->Rotation.y + 4000);

		if (data->Position.x > player->Position.x + 50) {
			data->Position.x -= 3;
		}
		else {
			data->Action++;
		}
		break;
	case tornadoTransition:
		player->Action = Action_Jump;
		co2->Speed.y += 2;
		data->Action++;
		break;
	case tornadoTransition2:
		data->Position.x -= 3;
		if (++data->field_6 == 20) {
			data->Action++;
		}
		break;
	case tornadoTransition3:

		LookAt(&data->Position, &player->Position, nullptr, &data->Rotation.y + 4000);

		data->field_6 = 0;
		player->Action = TornadoStanding;
		//player->Position.y = data->Position.y + 5;
		co2->AnimInfo.Next = 35;
		ControllerEnabled[pNum] = 1;
		data->Action++;

		break;
	case tornadoPlayable:
		Tornado_AbortCheckInput(co2, player);

		Mech_CallCheckInput(co2, data);

		if (!isTornadoOn) {
			data->Position = player->Position;
			data->Rotation.y = player->Rotation.y;

			data->Action = tornadoExit;
		}

		break;
	case tornadoTransfoMech:
		ControllerEnabled[pNum] = 0;
		mech = LoadObject(2, "Mech", CallMech, LoadObj_Data1);
		mech->Data1.Entity->Index = co2->PlayerNum;
		mech->Data1.Entity->Position = player->Position;
		mech->Data1.Entity->Rotation.y = player->Rotation.y;
		DeleteObject_(obj);
		break;
	case tornadoExit:
		data->Rotation.y = 0x4000;
		data->Position.x += 3;
		data->Position.y += 3;
		if (++data->field_6 == 100) {
			DeleteObject_(obj);
		}
		break;

	}
}


void Tornado_CommonPhysics(CharObj2Base* co2, EntityData1* data1, EntityData2* data2)
{
	PGetRotation(data1, data2, co2);
	SuperSonicGetAccel(data1, data2, co2);
	PGetSpeed(data1, co2, data2);
	PSetPosition(data1, data2, co2);
	PResetPosition(data1, data2, co2);
}


void Tornado_CommonPhysicsV(CharObj2Base* co2, EntityData1* data1, EntityData2* data2, float A, float B)
{
	co2->Speed.y = FloatCalcResult(co2->Speed.y, A, B);
	//PResetAngle(data1, co2);
	Tornado_CommonPhysics(co2, data1, data2);
}

void Tornado_SetNextAction(EntityData1* data1, char action) {
	data1->Action = action;
	return;
}

signed int isTornadoStanding(CharObj2Base* a1, EntityData1* a2)
{
	if ((a2->Status & 0x4000) == 0
		&& 0.0 != AnalogThings[a1->PlayerNum].magnitude
		&& ((a2->Status & Status_OnPath) != 0 || !a1->DisableControlTimer)
		|| 0.0 != a1->Speed.x)
	{
		return 0;
	}

	Tornado_SetNextAction(a2, TornadoStanding);
	a1->IdleTime = 0;
	return 1;
}

void Tornado_Standing(EntityData1* data1, CharObj2Base* co2)
{

	float spdY = 0.0;
	char pnum = co2->PlayerNum;

	if ((0.0 != AnalogThings[co2->PlayerNum].magnitude) || (data1->Status & Status_DisableControl))
	{
		Tornado_SetNextAction(data1, TornadoMoving);
		return;
	}

	if (Jump_Held[pnum])
	{
		spdY = 2.7;
		Tornado_SetNextAction(data1, TornadoAscending);
		data1->Status |= Status_Attack;
		if (co2->Speed.y >= 2.7)
		{
			VibeThing(0, 15, 0, 4);
		}
		co2->Speed.y = spdY;
		return;
	}
	if (!Action_Held[pnum])
	{
		return;
	}
	spdY = -4.5;
	Tornado_SetNextAction(data1, TornadoDescending);
	data1->Status |= Status_Attack;
	if (co2->Speed.y > spdY)
	{
		co2->Speed.y = spdY;
	}
	VibeThing(0, 15, 0, 4);
	return;
}

void Tornado_Moving(EntityData1* data1, CharObj2Base* co2)
{
	if (data1->NextAction != 0 || data1->Status & Status_DoNextAction || isTornadoStanding(co2, data1))
	{
		return;
	}

	float curSpeed = 0.0;
	char pnum = co2->PlayerNum;

	if (Jump_Held[pnum])
	{
		curSpeed = 2.7;
		Tornado_SetNextAction(data1, TornadoAscending);
		data1->Status |= Status_Attack;
		if (co2->Speed.y >= 2.7)
		{
			VibeThing(0, 15, co2->PlayerNum, 4);
			return;
		}
	}

	if (!Action_Held[pnum])
	{
		return;
	}

	Tornado_SetNextAction(data1, TornadoDescending);
	data1->Status |= Status_Attack;

	VibeThing(0, 15, co2->PlayerNum, 4);
	return;
}

void Tornado_Ascending(EntityData1* data1, CharObj2Base* co2)
{
	if (isTornadoStanding(co2, data1))
	{
		data1->Status &= ~Status_Attack;
		return;
	}

	if (!Jump_Held[co2->PlayerNum])
	{
		Tornado_SetNextAction(data1, TornadoMoving);
		data1->Status &= ~Status_Attack;
	}

	float spdY = 3.5f;

	if (co2->Speed.y < spdY)
	{
		co2->Speed.y += 0.5f;

	}
	else {
		co2->Speed.y = spdY;
	}

	return;
}

void Tornado_Descending(EntityData1* data1, CharObj2Base* co2)
{

	if (isTornadoStanding(co2, data1))
	{
		data1->Status &= ~Status_Attack;
		return;
	}

	if (!Action_Held[co2->PlayerNum])
	{
		Tornado_SetNextAction(data1, TornadoMoving);
		data1->Status &= ~Status_Attack;
	}

	float spdY = -3.5f;
	float rotZ = 10000;

	if (co2->Speed.y > spdY)
	{
		co2->Speed.y -= 0.5f;
	}
	else {
		co2->Speed.y = spdY;
	}

	return;
}


void Tornado_RunsActions(EntityData1* data1, CharObj2Base* co2) {

	switch (data1->Action)
	{
	case TornadoStanding:
		Tornado_Standing(data1, co2);
		return;
	case TornadoMoving:
		Tornado_Moving(data1, co2);
		return;
	case TornadoAscending:
		Tornado_Ascending(data1, co2);
		return;
	case TornadoDescending:
		Tornado_Descending(data1, co2);
		return;
	default:
		return;
	}
}

void Tornado_MainActions(EntityData1* data1, CharObj2Base* co2, EntityData2* data2)
{
	switch (data1->Action)
	{
	case TornadoStanding:
	case TornadoMoving:
		Tornado_CommonPhysics(co2, data1, data2);
		return;
	case TornadoAscending:
		Tornado_CommonPhysicsV(co2, data1, data2, 2.0f, 0.4f);
		return;
	case TornadoDescending:
		Tornado_CommonPhysicsV(co2, data1, data2, -2.0f, 0.4f);
		return;
	}
}

void LoadTornado_ModelAnim() {

	Tornado = LoadMDL("tornadoMDL", ModelFormat_Chunk);
	TornadoTransfo = LoadMDL("tornadoTransfoMDL", ModelFormat_Chunk);
	TornadoTransfoMotion = LoadAnim("TornadoTransfo");

	HMODULE** DLL = datadllhandle;

	if (!DLL)
		return;

	HMODULE dataDll = **DLL;

	if (!dataDll)
		return;

	FARPROC tornado_tex_dll = GetProcAddress(dataDll, "texlist_limtails");
	tornadoTex = (NJS_TEXLIST*)tornado_tex_dll;

	LoadTextureList("LIMTAILS", tornadoTex);
	LoadTextureList("tornadoTransfoTex", &tornadoTransfoTexList);
	return;
}