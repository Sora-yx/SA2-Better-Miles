#include "pch.h"
#include "tornado.h"

extern bool isTornadoTransform;

ModelInfo* Tornado = nullptr;
AnimationFile* TornadoMotion = nullptr;

NJS_TEXLIST* tornadoTex;
bool isTornadoOn = false;
bool cutsceneTornado = false;

Float ColRangeBackup = 0.0f;

bool isInTornado(char pNum) {

	if (!MainCharObj1[pNum])
		return false;

	return MainCharObj1[pNum]->Action >= TornadoStanding && MainCharObj1[pNum]->Action <= TornadoDescending;
}

void Mech_CallCheckInput(CharObj2Base* co2, EntityData1* data1) {

	if (GameState != GameStates_Ingame || !co2)
		return;

	if (Controllers[co2->PlayerNum].press & Buttons_Up && !isKeyboard() || isKeyboard() && GetKeyState('B') & 0x8000)
	{
		data1->Action = tornadoTransfoMech;
		return;
	}
}

void Tornado_BoostCheckInput(CharObj2Base* co2, EntityData1* data) {

	if (GameState != GameStates_Ingame || !co2)
		return;

	char pNum = co2->PlayerNum;

	if (data->Timer > 0) {
		data->Timer--;
		return;
	}

	if (Controllers[pNum].press & Buttons_Y && isInTornado(pNum))
	{
		PlayCustomSoundVolume(SE_tornadoBoost, 2);
		data->Timer = 120;
		co2->Speed.x += co2->PhysData.SpeedCapH - 4.0f;

		uint16_t randomVoice = rand() % 3;

		if (!randomVoice)
			return;

		randomVoice = randomVoice == 1 ? Voice_TailsWow : Voice_TailsYay;

		PlayCustomVoiceVolume(randomVoice, 1);
		return;
	}
}

void Tornado_CallCheckInput(CharObj2Base* co2, EntityData1* playerData) {

	if (GameState != GameStates_Ingame || !co2 || isTornadoOn || CurrentLevel >= LevelIDs_BigFoot)
		return;

	if (playerData->Action <= Action_Run)
	{
		if (Controllers[co2->PlayerNum].press & Buttons_Up && !isKeyboard() || isKeyboard() && GetKeyState('B') & 0x8000)
		{
			ObjectMaster* tornado = LoadObject(2, "Tornado", Tornado_Main, LoadObj_Data1);
			//PoseEffectMan_Load_(co2->PlayerNum, 186);
			tornado->Data1.Entity->Index = co2->PlayerNum;
			isTornadoOn = true;

			return;
		}
	}
}

void Tornado_AbortCheckInput(CharObj2Base* co2, EntityData1* playerData) {

	if (GameState != GameStates_Ingame || !co2)
		return;

	char pNum = co2->PlayerNum;

	if (Controllers[pNum].press & Buttons_Down && isInTornado(pNum) && !isKeyboard() || !isInTornado(pNum) && playerData->Action != Action_ObjectControl || isKeyboard() && GetKeyState('N') & 0x8000)
	{
		if (tornadoMusic)
		{
			StopMusic();
			ResetMusic();
		}

		isTornadoOn = false;
		co2->Speed.y += 3.0f;
		co2->AnimInfo.Next = 66;
		playerData->Action = Action_Fall;
		playerData->Collision->Range = ColRangeBackup;

		return;
	}
}

void Tornado_CancelNAct(CharObj2Base* co2, EntityData1* playerData, EntityData2* data2, TailsCharObj2* co2Miles, EntityData1* data)
{
	if (MilesCheckInput(data2, co2Miles, co2, playerData))
	{
		if (TimerStopped)
		{
			if (tornadoMusic)
			{
				StopMusic();
				ResetMusic();
			}
			isTornadoOn = false;
		}
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


void tornadoCam_Child(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* parentData = obj->Parent->Data1.Entity;
	char pNum = obj->Parent->Data1.Entity->Index;

	EntityData1* player = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	if (data->Action >= 3 && data->Action <= 6)
		CamEventPos = parentData->Position;

	switch (data->Action)
	{
	case 0:
		SetCameraFacePlayer(pNum, player, 20.0f);
		data->Action++;
		break;
	case 1:
		if (++data->Timer == 100)
		{

			ReleaseCamera(CameraData[pNum].currentCameraSlot, pNum);
			data->Action++;
		}
		break;
	case 2:
		data->Timer = 0;

		RegisterCameraMode(pNum, 20);
		SetAdjustMode(CameraData[pNum].currentCameraSlot, 0, 0);
		*(int*)0x1DCFDE0 = 3;
		*(int*)0x1DCFDE4 = 0;
		*(int*)0x1DCFDE8 = 0;
		CameraEventZoom = 600.0f;
		CamEventPos = player->Position;
		CamEventAngleZ = 63488;
		CamEventAngleY = parentData->Rotation.y - 0x4000;
		PlayCustomSoundVolume(SE_tornadoBoost, 2);
		data->Action++;
		break;
	case 3:
		CameraEventZoom -= 8;
		if (++data->Timer == 60)
		{
			CameraEventZoom = 50.0f;
			CamEventAngleY = parentData->Rotation.y + 0x8000;
			data->Action++;
			data->Timer = 0;
		}
		break;
	case 4:
		if (++data->Timer == 60)
		{
			CamEventAngleY = parentData->Rotation.y + 0x4000;
			data->Action++;
			data->Timer = 0;
		}
		break;
	case 5:

		if (++data->Timer == 100)
		{
			ReleaseCamera(CameraData[pNum].currentCameraSlot, pNum);
			data->Action++;

		}
		break;
	default:
		DeleteObject_(obj);
		break;
	}
}

void Tornado_Delete(ObjectMaster* obj)
{
	isTornadoOn = false;
}

void Tornado_Main(ObjectMaster* obj) {

	EntityData1* data = obj->Data1.Entity;
	char pNum = data->Index;

	EntityData1* player = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];

	ObjectMaster* mech;

	if (!player || !co2)
		return;

	Angle angy = njArcTan2((player->Position.x, data->Rotation.y), (player->Position.z, data->Rotation.y));

	switch (data->Action)
	{
	case tornadoInit:

		co2->Powerups |= Powerups_Invincibility;

		if (isInMech)
		{
			isTornadoOn = true;
			isInMech = false;
			obj->DisplaySub = Tornado_Display;
			data->Position = player->Position;
			player->Action = TornadoStanding;
			co2->AnimInfo.Next = 35;
			data->Action = tornadoPlayable;
			PlayCustomSound_Entity(SE_tornadoFlying, obj, 300, true);
			return;
		}

		obj->DisplaySub = Tornado_Display;
		obj->DeleteSub = Tornado_Delete;
		ControllerEnabled[pNum] = 0;
		DeathZoneDebug = 1;
		if (tornadoMusic)
			PlayJingle("tornado.adx");

		player->Rotation = data->Rotation;
		player->Action = ObjectControl;
		co2->AnimInfo.Next = 0;
		data->Position = player->Position;
		data->Position.y = data->Position.y + 20.0f;


		if (!cutsceneTornado)
		{
			PlayCustomVoice(Voice_TailsTimeToJam);
			DrawSubtitles(1, "\a Time to jam!", 95, 1);
			LoadChildObject(LoadObj_Data1, tornadoCam_Child, obj);

			data->Position.x += 1020.0f;

			data->Action++;
		}
		else
		{
			isTornadoOn = true;
			data->Position.x += 50.0f;
			data->Action = tornadoMoveToPlayer2;
		}

		break;
	case tornadoCall:
		if (++data->Timer == 50)
		{
			PlayCustomSound_Entity(SE_tornadoFlying, obj, 500, true);
			data->Action++;
		}
		break;
	case tornadoMoveToPlayer1:
		player->Rotation.y = angy;
		data->Rotation.y = -player->Rotation.y;

		if (data->Position.x > player->Position.x + 650.0f) {
			data->Position.x -= 8;
		}
		else {
			data->Timer = 0;

			data->Action++;
		}
		break;
	case tornadoMoveToPlayer2:
		player->Rotation.y = angy;
		data->Rotation.y = -player->Rotation.y;
		if (data->Position.x > player->Position.x + 70.0f) {
			data->Position.x -= 3;
		}
		else {

			cutsceneTornado = true;
			data->Action++;
		}
		break;
	case tornadoTransition:
		player->Action = Action_Jump;
		co2->AnimInfo.Next = 66;
		co2->Speed.y += 2.0f;
		data->Action++;
		break;
	case tornadoTransition2:
		data->Position.x -= 3;
		if (++data->Timer == 20) {

			player->Rotation = data->Rotation;
			player->Rotation.y = 0x8000 - data->Rotation.y;
			data->Action++;
		}
		break;
	case tornadoTransition3:

		data->Timer = 0;
		player->Action = TornadoStanding;
		co2->AnimInfo.Next = 35;
		ControllerEnabled[pNum] = 1;

		ColRangeBackup = player->Collision->Range;
		player->Collision->Range *= 5.0f;
		DeathZoneDebug = 0;
		data->Action++;

		break;
	case tornadoPlayable:
		if (isTornadoOn)
		{
			Tornado_CancelNAct(co2, player, MainCharData2[pNum], MilesCO2Extern, data);
			Tornado_AbortCheckInput(co2, player);
			Tornado_BoostCheckInput(co2, data);
			Mech_CallCheckInput(co2, data);
		}
		else
		{
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
		return;
	case tornadoExit:
		data->Rotation.y = 0x4000;
		data->Position.x += 3;
		data->Position.y += 3;

		if (++data->Timer == 100)
		{
			co2->Powerups &= ~Powerups_Invincibility;
			DeleteObject_(obj);
		}
		break;
	}
}

void Tornado_CommonPhysics(CharObj2Base* co2, EntityData1* data1, EntityData2* data2)
{
	PResetAngle(data1, co2);
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
		&& 0.0f != AnalogThings[a1->PlayerNum].magnitude
		&& ((a2->Status & Status_OnPath) != 0 || !a1->DisableControlTimer)
		|| 0.0f != a1->Speed.x)
	{
		return 0;
	}

	Tornado_SetNextAction(a2, TornadoStanding);
	a1->IdleTime = 0;
	return 1;
}

void Tornado_Standing(EntityData1* data1, CharObj2Base* co2)
{

	float spdY = 0.0f;
	char pnum = co2->PlayerNum;

	if ((0.0f != AnalogThings[co2->PlayerNum].magnitude) || (data1->Status & Status_DisableControl))
	{
		Tornado_SetNextAction(data1, TornadoMoving);
		return;
	}

	if (Jump_Held[pnum])
	{
		spdY = 2.7f;
		Tornado_SetNextAction(data1, TornadoAscending);
		data1->Status |= Status_Attack;
		if (co2->Speed.y >= 2.7f)
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

	float spdY = -3.8f;
	float rotZ = 10000;

	if (co2->Speed.y > spdY)
	{
		co2->Speed.y -= 0.7f;
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
	if (!co2 || co2->CharID2 != Characters_Tails)
		return;

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

	if (!Tornado)
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
	Load_TornadoTransfo_ModelsTextures();

	return;
}

void Delete_Tornado() {
	Tornado = nullptr;
	TornadoMotion = nullptr;
	isTornadoOn = false;
	isTornadoTransform = false;
	FreeAnim(TornadoMotion);
	FreeMDL(Tornado);
	return;
}
