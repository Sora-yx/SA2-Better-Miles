#include "pch.h"
#include "patches.h"

//miscellaneous fixes 
TaskHook Levelitem_t((intptr_t)LevelItem_Load);

UsercallFuncVoid(TailsCalcColDamage_t, (TailsCharObj2* a1, taskwk* a2), (a1, a2), 0x753090, rECX, rESI);
FunctionHook<void, taskwk*, playerwk*, TailsCharObj2_r*> Miles_ManageTails_t(0x751090);


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

//rewrite the function that manage Miles's tails so they aren't static when you move + fix their pos when spinning in the air
void __cdecl Miles_ManageTails_r(taskwk* twp, playerwk* pwp, TailsCharObj2_r* Mpwp)
{
	auto curAction = twp->mode;

	if ( curAction == Flying || twp->mode == Running && pwp->spd.x >= 2.0f)
	{
		return Miles_ManageTails_t.Original(twp, pwp, Mpwp);
	}

	Float tailSPD = twp->pos.y + 2.5f - *(float*)&Mpwp->field_4BC[20];

	if (tailSPD < 0.0f)
	{
		tailSPD = 0.0f;
	}

	Mpwp->tailJiggle0->speed = tailSPD;
	Mpwp->tailJiggle1->speed = tailSPD;

	auto jiggle0 = Mpwp->tailJiggle0;
	auto jiggle1 = Mpwp->tailJiggle1;
	auto Jig0SourceModelCopy = Mpwp->tailJiggle0->SourceModelCopy;
	auto Jig1SourceModelCopy = Mpwp->tailJiggle1->SourceModelCopy;
	int angleForSomething = 0;
	Float ZIdk = 0.0f;

	if (curAction == Spinning || curAction == SpinningAir)
	{
		if (jiggle0->type != 9)
		{
			for (uint8_t i = 0; i < 3; i++)
			{
				Jig0SourceModelCopy->ang[i] = 0;
				Jig1SourceModelCopy->ang[i] = 0;
			}

			//reset tail angle properly (fix tail rot when swapping to spin while running)
			for (uint16_t i = 100; i < LengthOfArray(Mpwp->field_3BC); i++)
			{
				Mpwp->field_3BC[i] = 0;
			}

			jiggle0->field_24 = { 0, 0, 0 };
			*(DWORD*)jiggle0->gap30 = 0;
			jiggle1->field_24 = { 0, 0, 0 };
			*(DWORD*)jiggle1->gap30 = 0;

			jiggle0->type = 9;
			Mpwp->tailJiggle1->type = 9;
		}
		*(DWORD*)&Mpwp->field_3BC[136] += *(DWORD*)&Mpwp->field_3BC[132];
		Jig0SourceModelCopy->ang[0] = BAMS_SubWrap(49152, 4096, Jig0SourceModelCopy->ang[0]);
		Jig1SourceModelCopy->ang[0] = BAMS_SubWrap(0x4000, 4096, Jig1SourceModelCopy->ang[0]);
		Jig0SourceModelCopy->ang[1] = BAMS_SubWrap(0, 4096, Jig0SourceModelCopy->ang[1]);
		Jig1SourceModelCopy->ang[1] = BAMS_SubWrap(0, 4096, Jig1SourceModelCopy->ang[1]);
		angleForSomething = BAMS_SubWrap(4096, 0x2000, *(_DWORD*)&Mpwp->field_3BC[140]);
	}
	else
	{

		if (jiggle0->type == 8 || jiggle0->type == 9)
		{
			jiggle0->type = 12;
			Mpwp->tailJiggle1->type = 12;
			Mpwp->tailJiggle0->field_C = 0;
			Mpwp->tailJiggle0->field_24.x = 0.0f;
			Mpwp->tailJiggle0->field_24.y = 0.0f;
			Mpwp->tailJiggle0->field_24.z = 0.0f;
			*(_DWORD*)Mpwp->tailJiggle0->gap30 = 0;
			Mpwp->tailJiggle1->field_C = 0;
			Mpwp->tailJiggle1->field_24.x = 0.0;
			Mpwp->tailJiggle1->field_24.y = 0.0;
			Mpwp->tailJiggle1->field_24.z = 0.0;
			*(_DWORD*)Mpwp->tailJiggle1->gap30 = 0;
			if (twp->mode == 6)
			{
				Mpwp->tailJiggle1->field_C = dword_1AF017C;
				Mpwp->tailJiggle0->field_C = dword_1AF017C;
			}
		}
		else
		{

			if (jiggle1->type == 12)
			{
				auto v15 = jiggle1->field_C;
				auto v16 = v15 < dword_1AF0180;
				jiggle1->field_C = v15 + 1;
				if (!v16 && !*(_DWORD*)&Mpwp->field_3BC[136])
				{
					Mpwp->tailJiggle0->type = 6;
					Mpwp->tailJiggle1->type = 6;
					Mpwp->tailJiggle0->field_10 = 0;
					Mpwp->tailJiggle0->field_C = 0;
					Mpwp->tailJiggle0->field_8 = 0;
					Mpwp->tailJiggle1->field_10 = 0;
					Mpwp->tailJiggle1->field_C = 0;
					Mpwp->tailJiggle1->field_8 = 0;
				}
			}
			else
			{
				//originally the game takes the position of the player and the tails so when you move the tails get static, we don't want that.
				NJS_POINT3 pos = { 0.0f, 0.0f, 0.0f };

				auto v20 = (twp->ang.y) - (Mpwp->tailIdk);
				PConvertVector_G2P((EntityData1*)twp, &pos);
				auto curAction2 = twp->mode;
				auto v21 = v20;


				auto v23 = pos.x;
				auto v24 = pos.y;
				auto v25 = pos.z;
				auto v26 = (NJS_VECTOR*)&Mpwp->tailJiggle0->field_24;
				v26->x = pos.x;
				v26->y = v24;
				v26->z = v25;
				*(_DWORD*)&Mpwp->tailJiggle0->gap30 = v21;

				jiggle0->field_C -= 1;
				if (jiggle0->field_C <= 0)
				{
					Mpwp->tailJiggle0->field_10 = (int)((double)rand() * 0.000030517578125f * 128.0f + 448.0f);
					Mpwp->tailJiggle0->field_C = (int)((double)rand() * 0.000030517578125f * (double)dword_1AF0178
						+ (double)dword_1AF0174);
				}

				if (jiggle0->field_10)
				{
					jiggle0->field_8 += jiggle0->field_10;
					Mpwp->tailJiggle0->field_24.y = njSin(Mpwp->tailJiggle0->field_8) * -0.07999999821186066f;
				}
				auto v31 = pos.z;
				auto v32 = &Mpwp->tailJiggle1->field_24;
				v32->x = v23;
				v32->y = v24;
				v32->z = v31;
				*(DWORD*)Mpwp->tailJiggle1->gap30 = v21;

				auto v34 = jiggle1->field_C;
				jiggle1->field_C = v34 - 1;
				if (v34 <= 0)
				{
					Mpwp->tailJiggle1->field_10 = (int)((double)rand() * 0.000030517578125 * 128.0 + 448.0);
					Mpwp->tailJiggle1->field_C = (int)((double)rand() * 0.000030517578125 * (double)dword_1AF0178
						+ (double)dword_1AF0174);
				}

				auto v36 = Mpwp->tailJiggle0->field_8 - jiggle1->field_8;
				if (v36 < 0)
				{
					v36 = jiggle1->field_8 - Mpwp->tailJiggle0->field_8;
				}
				if ((unsigned __int16)v36 < 0x6000u)
				{
					jiggle1->field_10 = (int)((double)jiggle1->field_10 * 0.9800000190734863);;
				}

				auto v38 = jiggle1->field_10;
				if (v38)
				{
					jiggle1->field_8 += v38;

					auto v40 = njSin(jiggle1->field_8);
					auto v41 = dword_1AF0188;
					auto v42 = dword_1AF0184;
					jiggle1->field_24.y = v40 * -0.07999999821186066;

					jiggle1->field_10 = BAMS_SubWrap(v42, v41, jiggle1->field_10);
				}



				Float v50 = 0.0f;


				if (jiggle0->type == 7)
				{
					v50 = 0.0f;
				}
				else
				{
					jiggle0->field_24.x = 10.0f;
					v50 = 0.0;
					Mpwp->tailJiggle0->field_24.y = 0.0f;
					Mpwp->tailJiggle0->field_24.z = 0.0f;
				}

				ZIdk = v50;
				if (jiggle1->type != 7)
				{
					jiggle1->field_24.x = 10.0f;
					Mpwp->tailJiggle1->field_24.y = v50;
					Mpwp->tailJiggle1->field_24.z = v50;
				}
				Mpwp->tailJiggle0->type = 7;
				Mpwp->tailJiggle1->type = 7;


				auto curAnim = (__int16)pwp->mj.lastaction;
				{

					if (jiggle0->field_34[31] < 8.0f)
					{
						jiggle0->field_24.x = 2.0f;
						jiggle0->field_24.y = 0.40000001f;
						jiggle0->field_24.z = ZIdk;
					}

					if (jiggle1->field_34[31] < 8.0f)
					{
						jiggle1->field_24.x = 2.0f;
						Mpwp->tailJiggle1->field_24.y = 0.40000001f;
						Mpwp->tailJiggle1->field_24.z = ZIdk;
					}
				}
			}
		}

		Angle v57 = BAMS_SubWrap(0, 2048, *(_DWORD*)&Mpwp->field_3BC[132]);
		*(_DWORD*)&Mpwp->field_3BC[136] += v57;
		Angle v58 = *(_DWORD*)&Mpwp->field_3BC[136];
		*(_DWORD*)&Mpwp->field_3BC[132] = v57;
		if (!v57)
		{
			*(_DWORD*)&Mpwp->field_3BC[136] = BAMS_SubWrap(0, 2048, v58);
		}

		Jig0SourceModelCopy->ang[0] = BAMS_SubWrap(60928, 0x8000, Jig0SourceModelCopy->ang[0]);
		Jig1SourceModelCopy->ang[0] = BAMS_SubWrap(4608, 0x8000, Jig1SourceModelCopy->ang[0]);
		Jig0SourceModelCopy->ang[1] = BAMS_SubWrap(0, 0x8000, Jig0SourceModelCopy->ang[1]);
		Jig1SourceModelCopy->ang[1] = BAMS_SubWrap(0, 0x8000, Jig1SourceModelCopy->ang[1]);
		angleForSomething = BAMS_SubWrap(0, 2048, *(_DWORD*)&Mpwp->field_3BC[140]);
	}

	*(_DWORD*)&Mpwp->field_3BC[140] = angleForSomething;
	DoJiggleThing(Mpwp->tailJiggle0);
	DoJiggleThing(Mpwp->tailJiggle1);
	Mpwp->tailOriginPos = twp->pos;
	Mpwp->tailIdk = twp->ang.y;
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

			if (index >= 0 && index < 300)
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