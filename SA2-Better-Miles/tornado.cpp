#include "pch.h"

ModelInfo* Tornado = nullptr;
AnimationFile* TornadoMotion = nullptr;


NJS_TEXLIST* tornadoTex;

bool isTornadoOn = false;

bool isInTornado(char pNum) {
	if (!MainCharObj1[pNum])
		return false;
	
	return MainCharObj1[pNum]->Action >= TornadoStanding && MainCharObj1[pNum]->Action <= TornadoDescending;
}

void DeleteAndLoadMiles(char pNum) {

	ObjectMaster* player = MainCharacter[pNum];
	player->Data1.Entity->Action = 0;
	player->MainSub = nullptr;
	player->DisplaySub = nullptr;
	player->field_2C = nullptr;

	MechEggman_Delete(player);
	CurrentCharacter = Characters_Tails;
	LoadTails(pNum);
	InitCharacterSound();
	return;
}

NJS_VECTOR SavePos = { 0, 0, 0 };

void DeleteAndLoadMech(char pNum) {

	ObjectMaster* player = MainCharacter[pNum];
	player->Data1.Entity->Action = 0;
	player->MainSub = nullptr;
	player->DisplaySub = nullptr;
	player->field_2C = nullptr;

	Tails_Delete(player);
	CurrentCharacter = Characters_MechTails;
	LoadMechTails(pNum);
	InitCharacterSound();
	return;
}


void CallMech(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	switch (data->Action)
	{
	case 0:
	{
		SavePos = playerData->Position;
		DeleteAndLoadMech(pNum);
		InitCharacterSound();
		data->Action++;
	}
	break;
	case 1:

		if (++data->field_6 == 8)
		{
			playerData->Position = SavePos;
			PlayVoice(2, 2433);
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

	if (data->Action != 5) {
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




void Tornado_CheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (GameState != GameStates_Ingame || !co2 || isTornadoOn)
		return;

	if (Controllers[co2->PlayerNum].on & Buttons_Y && Controllers[co2->PlayerNum].press & Buttons_Right)
	{
		//CallMech(co2, data1);
		isTornadoOn = true;
		ObjectMaster* tornado = LoadObject(2, "Tornado", LoadTornado, LoadObj_Data1);
		tornado->Data1.Entity->Index = co2->PlayerNum;

		return;
	}
}

void Tornado_AbortCheckInput(CharObj2Base* co2, EntityData1* data1) {

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
		data1->Action = Action_Fall;

		return;
	}
}

void LoadTornado(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;

	EntityData1* player = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	ObjectMaster* mech;

	if (!player)
		return;

	switch (data->Action)
	{
	case 0:
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
	case 1:

		LookAt(&data->Position, &player->Position, nullptr, &data->Rotation.y + 4000);

		if (data->Position.x > player->Position.x + 50) {
			data->Position.x -= 3;
		}
		else {
			data->Action++;
		}
		break;
	case 2:
		player->Action = Action_Jump;
		co2->Speed.y += 2;
		data->Action++;
		break;
	case 3:
		data->Position.x -= 3;
		if (++data->field_6 == 20) {
			data->Action++;
		}
		break;
	case 4:

		LookAt(&data->Position, &player->Position, nullptr, &data->Rotation.y + 4000);

		data->field_6 = 0;
		player->Action = TornadoStanding;
		//player->Position.y = data->Position.y + 5;
		co2->AnimInfo.Next = 35;
		ControllerEnabled[pNum] = 1;
		data->Action++;

		break;
	case 5:
		Tornado_AbortCheckInput(co2, player);

		if (!isTornadoOn) {
			data->Position = player->Position;
			data->Rotation.y = player->Rotation.y;

			data->Action = 7;
		}

		break;
	case 6:
		mech = LoadObject(2, "Mech", CallMech, LoadObj_Data1);
		mech->Data1.Entity->Index = co2->PlayerNum;
		DeleteObject_(obj);
		break;
	case 7:
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

	HMODULE** DLL = datadllhandle;

	if (!DLL)
		return;

	HMODULE dataDll = **DLL;

	if (!dataDll)
		return;

	FARPROC tornado_tex_dll = GetProcAddress(dataDll, "texlist_limtails");
	tornadoTex = (NJS_TEXLIST*)tornado_tex_dll;

	LoadTextureList("LIMTAILS", tornadoTex);
	return;
}