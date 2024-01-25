#include "pch.h"
#include "patches.h"

//miscellaneous fixes 
TaskHook Levelitem_t((intptr_t)LevelItem_Load);

UsercallFuncVoid(TailsCalcColDamage_t, (TailsCharObj2* a1, taskwk* a2), (a1, a2), 0x753090, rECX, rESI);
FunctionHook<void, EntityData1*, CharObj2Base*, TailsCharObj2*> Miles_ManageTails_t(0x751090);


//used to make tails actually do damage since unlike regular character he doesn't have code for
//this is mostly a port of sonic col damage


void TailsCalcColDamage_r(TailsCharObj2* co2M, taskwk* twp)
{
	TailsCalcColDamage_t.Original(co2M, twp);

	auto col = twp->cwp;

	if (!col)
		return;

	TailsCharObj2_* co2T = (TailsCharObj2_*)co2M;
	CharObj2Base* pwp = &co2M->base;

	auto colInfo = col->info;
	colInfo->attr &= 0xFFFFBFFF;	
	unsigned int attrCol = colInfo->attr;

	int colFlag1 = 0;
	int colFlag2 = 0;

	if (pwp->Powerups >= 0)
	{
		if ((pwp->Upgrades & Upgrades_SuperSonic) != 0)
		{
			colFlag1 = 3;
			colFlag2 = 3;
		}
		else
		{

			if (twp->mode == SpinningAir)
			{
				twp->cwp->info[1].attr &= 0xFFFFFFEF;
				twp->cwp->info[2].attr &= 0xFFFFFFEF;

				twp->cwp->info[1].center = co2T->tailVector0;
				twp->cwp->info[2].center = co2T->tailVector1;
				WriteData<1>((int*)0x74FD8B, SpinningAir); //hacky way to get damage on the tails in the air
			}
			else
			{
				WriteData<1>((int*)0x74FD8B, 60); //restore original
			}


			switch (twp->mode)
			{
			case LightDash:
				colFlag1 = 1;
				colFlag2 = 3;
				break;
			case Bounce:
				colFlag1 = 2;
				colFlag2 = 1;
				colInfo->attr = attrCol | 0x4000;
				break;
			case Spinning:
			case SpinningAir:
				colInfo[1].a = 8.0f;
				colInfo[2].a = 8.0f;
				break;
			default:
				if ((twp->flag & Status_Attack) != 0)
				{
					colFlag1 = 1;
					colFlag2 = 1;
					if (twp->mode == Rolling)
					{
						colInfo->attr = attrCol | 0x4000;
					}
				}
				else
				{
					colFlag1 = 0;
					colFlag2 = 0;
				}
				break;
			}
		}
	}
	else
	{
		colFlag1 = 3;
		colFlag2 = 3;

	}

	colInfo->damage = colInfo->damage & 0xF0 | colFlag1 & 3 | (4 * (colFlag2 & 3));
}

void CheckAndSetPlayerSpeed_r(int pid)
{
	EntityData1* data1 = MainCharObj1[pid];

	if (!data1)
		return;

	int charID = MainCharObj2[pid]->CharID;
	__int16 status = data1->Status;

	if ((status & Status_Attack) != 0
		&& (status & (Status_OnObjectColli | Status_Ground)) == 0
		&& ((charID) == Characters_Sonic || charID == Characters_Shadow
			|| (charID == Characters_Knuckles || charID == Characters_Rouge
				|| charID == Characters_Tails || charID == Characters_Eggman)
			&& (data1->Action == Action_Jump || data1->Action == Action_Punch3Run)))
	{

		NJS_VECTOR spd;
		spd.z = Gravity.z * -2.0f;
		spd.y = Gravity.y * -2.0f;
		spd.x = Gravity.x * -2.0f;
		SetPlayerSpeed(pid, spd.x, spd.y, spd.z);
		VibeThing(0, 15, pid, 6);
	}
}

static void __declspec(naked) CheckAndSetPlayerSpeed()
{
	__asm
	{
		push esi
		call CheckAndSetPlayerSpeed_r
		pop esi
		retn
	}
}

void SetSpacePhysics(CharObj2Base* co2) {
	switch (CurrentLevel)
	{
	case LevelIDs_FinalRush:
	case LevelIDs_MeteorHerd:
	case LevelIDs_FinalChase:
	case LevelIDs_CosmicWall:
	case LevelIDs_MadSpace:
	case LevelIDs_PlanetQuest:
	case LevelIDs_CosmicWall2P:
		co2->PhysData.AirResist = -0.0070000002f;
		co2->PhysData.AirDecel = -0.018999999f;
		break;
	}

	return;
}


void Miles_DisplayAfterImage(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3)
{
	if ((FrameCountIngame & 1) == 0 && a2->CharID == Characters_Tails && CharacterModels[208].Model)
	{
		NJS_OBJECT* obj = CharacterModels[208].Model;
		njPushMatrix(flt_25F02A0);

		njTranslateEx(&a1->Position);

		NJS_MATRIX_PTR matrix = _nj_current_matrix_ptr_;

		njRotateZ(matrix, a1->Rotation.z);
		njRotateX(matrix, a1->Rotation.x);
		njRotateY(matrix, 0x8000 - a1->Rotation.y);

		if (!TwoPlayerMode)
		{
			PlayerAfterimage(obj, 0, a3->TextureList, 0.0f, 0);
		}

		njPopMatrix(1u);
	}
}


void Miles_DrawTail(NJS_OBJECT* Tail, int(__cdecl* callback)(NJS_CNK_MODEL*)) {

	if (MilesCO2Extern) 
	{
		char pNum = MilesCO2Extern->base.PlayerNum;
		char curAnim = MainCharObj2[pNum]->AnimInfo.Current;
		int model = MilesCO2Extern->base.AnimInfo.Animations[curAnim].ModelNum;

		if ((model == jmpBallID || isSA1Char(Characters_Tails) && model == 255 || isJumpBall && MainCharObj1[pNum]->Status & Status_Ball) || MainCharObj1[pNum]->Action == Rolling || isInTornado(pNum))
			return;
	}

	NJS_POINT3 pos = { 0.0, -0.2f, 0.0 };
	njTranslateV(0, &pos);
	ProcessChunkModelsWithCallback(Tail, ProcessChunkModel);
}

//Many animations make Miles's tails in a very weird rotation, we force a specific rotation so they look decent here.
void CheckAndFixTailsRotation(CharObj2Base* co2, TailsCharObj2* co2Miles) 
{
	if (co2->AnimInfo.Current == 74 || co2->AnimInfo.Current >= 121 && co2->AnimInfo.Current <= 130 || co2->AnimInfo.Current >= 195 && co2->AnimInfo.Current <= 197)
		*(_DWORD*)&co2Miles->field_3BC[140] = -9000;
}

void SetNewTailsRotation(TailsCharObj2* co2Miles, int angle)
{
	*(_DWORD*)&co2Miles->field_3BC[140] = angle;
}

void LevelItem_r(ObjectMaster* tp)
{
	if (!MainCharObj2[0] || MainCharObj2[0]->CharID2 != Characters_Tails)
	{
		Levelitem_t.Original(tp);
	}
}

int BAMS_SubWrap(int result, int ang0, __int16 ang1)
{
	result = (unsigned __int16)result;
	if ((__int16)(result - ang1) > ang0 || (__int16)(result - ang1) < -ang0)
	{
		if ((((WORD)result - ang1) & 0x8000) != 0)
		{
			result = (unsigned __int16)(ang1 - ang0);
		}
		else
		{
			result = (unsigned __int16)(ang1 + ang0);
		}
	}
	return result;
}


void fixRocketGrab_r(task* obj)
{
	auto data = obj->Data1.twp;

	if (CurrentCharacter == Characters_Tails)
	{
		if (data)
		{
			data->cwp->info->attr |= 0x40000u; //fix rocket dammage lol
			data->cwp->flag &= 0xFFBFu;
		}
	}

	return AddToCollisionList((ObjectMaster*)obj);
}

static void __declspec(naked) fixRocketGrabASM()
{
	__asm
	{
		push esi
		call fixRocketGrab_r
		pop esi
		retn
	}
}

char field_3BCBackup[15]{ 0 };
void __cdecl Miles_ManageTails_r(EntityData1* data1, CharObj2Base* a2, TailsCharObj2* a3)
{
	if (!data1 || data1->Action != SpinningAir)
	{
		if (data1 && data1->Action == Spinning)
		{
			memcpy(&a3->field_3BC[125], field_3BCBackup, sizeof(field_3BCBackup));
		}
		return Miles_ManageTails_t.Original(data1, a2, a3);
	}


	memcpy(&a3->field_3BC[125], field_3BCBackup, sizeof(field_3BCBackup));;
	int angle = 0;

	Float TailPos = data1->Position.y + 2.5f - *(float*)&a3->field_4BC[20];

	if (TailPos < 0.0f)
	{
		TailPos = 0.0f;
	}

	*(float*)(*(_DWORD*)&a3->field_3BC[196] + 4) = TailPos;
	*(float*)(*(_DWORD*)&a3->field_3BC[200] + 4) = TailPos;

	int curAction = data1->Action;

	auto v7 = *(BYTE**)&a3->field_3BC[196];
	if (*v7 != 9)
	{
		*v7 = 9;
		**(BYTE**)&a3->field_3BC[200] = 9;
	}
	*(_DWORD*)&a3->field_3BC[136] += *(_DWORD*)&a3->field_3BC[132];
	auto v8 = *(_DWORD*)(*(_DWORD*)&a3->field_3BC[196] + 24);
	*(_DWORD*)(v8 + 20) = BAMS_SubWrap(49152, 4096, *(_DWORD*)(v8 + 20));
	auto v9 = *(_DWORD*)(*(_DWORD*)&a3->field_3BC[200] + 24);
	*(_DWORD*)(v9 + 20) = BAMS_SubWrap(0x4000, 4096, *(_DWORD*)(v9 + 20));
	auto v10 = *(_DWORD*)(*(_DWORD*)&a3->field_3BC[196] + 24);
	*(_DWORD*)(v10 + 24) = BAMS_SubWrap(0, 4096, *(_DWORD*)(v10 + 24));
	auto v11 = *(_DWORD*)(*(_DWORD*)&a3->field_3BC[200] + 24);
	*(_DWORD*)(v11 + 24) = BAMS_SubWrap(0, 4096, *(_DWORD*)(v11 + 24));
	angle = BAMS_SubWrap(4096, 0x2000, *(_DWORD*)&a3->field_3BC[140]);

	*(_DWORD*)&a3->field_3BC[140] = angle;

	DoJiggleThing(*(JiggleInfo**)&a3->field_3BC[196]);
	DoJiggleThing(*(JiggleInfo**)&a3->field_3BC[200]);
	*(Float*)&a3->field_3BC[156] = data1->Position.x;
	*(Float*)&a3->field_3BC[160] = data1->Position.y;
	*(Float*)&a3->field_3BC[164] = data1->Position.z;
	*(_DWORD*)&a3->field_3BC[192] = data1->Rotation.y;
}


AnimationIndex* GetAnimFromDLL(const char* lvlName)
{
	if (datadllhandle)
	{
		auto dataDLL = **datadllhandle;

		if (dataDLL)
		{
			return (AnimationIndex*)GetProcAddress(dataDLL, lvlName);
		}
	}

	return nullptr;
}

//because of how the game handle anims, we need to unload the stage anims so they don't override the mech tails ones when swapping
void UnloadLevelCharAnims(AnimationIndex* lvlAnim)
{
	if (!lvlAnim)
		return;

	if (lvlAnim[0].Index != UINT16_MAX)
	{
		uint16_t index = lvlAnim[0].Index;
		AnimationIndex* curLvlAnim = lvlAnim;
		uint16_t count = 0;
		uint16_t failsafe = 0;
		do
		{
			if (failsafe >= 301) //just to be super safe
				break;

			if (index  >= 0 && index < 300)
			{
				NJS_MOTION* curCharAnim = CharacterAnimations[index].Animation;
				if (curCharAnim == curLvlAnim->Animation)
				{
					CharacterAnimations[index].Animation = 0;
					CharacterAnimations[index].Count = 0;
				}
			}
			index = lvlAnim[++count].Index;		
			curLvlAnim = &lvlAnim[count];
			failsafe++;
		} while (index != UINT16_MAX);
	}
}

void UnloadLevelCharAnims()
{
	switch (CurrentLevel)
	{
	case LevelIDs_GreenForest:
		UnloadLevelCharAnims(GreenForestCharAnims);
		break;
	case LevelIDs_WhiteJungle:
		UnloadLevelCharAnims(WhiteJungleCharAnims_);
		break;
	case LevelIDs_MetalHarbor:
		UnloadLevelCharAnims(GetAnimFromDLL("header_stg10"));
		break;
	case LevelIDs_CityEscape:
		UnloadLevelCharAnims(GetAnimFromDLL("header_stg13"));
		break;
	}
}

void ReloadLevelCharAnims()
{
	switch (CurrentLevel)
	{
	case LevelIDs_GreenForest:
		LoadGreenForestCharAnims();
		break;
	case LevelIDs_WhiteJungle:
		LoadWhiteJungleCharAnims();
		break;
	case LevelIDs_MetalHarbor:
		LoadMetalHarborCharAnims();
		break;
	case LevelIDs_CityEscape:
		LoadCityEscapeCharAnims();
		break;
	}
}

void init_Patches()
{

	TailsCalcColDamage_t.Hook(TailsCalcColDamage_r);
	WriteJump((void*)0x47A9C0, CheckAndSetPlayerSpeed); //make Miles bouncing when hitting enemy like other characters

	//fixes "static" Miles's Tails
	WriteJump(reinterpret_cast<void*>(0x7512ea), (void*)0x7512F2); 
	WriteData<2>((int*)0x751529, 0x90);
	
	WriteCall((void*)0x6D6324, fixRocketGrabASM);

	//Draw the tails depending on the action
	WriteCall((void*)0x750B32, Miles_DrawTail);
	WriteCall((void*)0x750BB8, Miles_DrawTail);

	Levelitem_t.Hook(LevelItem_r);
	Miles_ManageTails_t.Hook(Miles_ManageTails_r);

	if (!isCharaSelect())
		WriteJump((void*)0x43C9D0, (void*)0x43CADF); // Tails/Eggman fix

}