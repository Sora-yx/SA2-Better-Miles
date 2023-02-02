#include "pch.h"

//miscellaneous fixes 
TaskHook Levelitem_t((intptr_t)LevelItem_Load);

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
		spd.z  = Gravity.z * -2.0f;
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
		co2->PhysData.AirResist = -0.0070000002;
		co2->PhysData.AirDecel = -0.018999999;
		break;
	}

	return;
}

int ActionArray[7] = { Jumping, 24, ObjectControl, Pulley, 66, VictoryPose };

//Edit the function which checks where it needs to animate Miles's tails to add more actions.
static const void* const loc_7512F2 = (void*)0x7512F2;
__declspec(naked) void  CheckAnimateTailsAction() {

	for (int i = 0; i < LengthOfArray(ActionArray); i++)
	{
		if (MainCharObj1[0]->Action != ActionArray[i])
		{
			_asm jmp loc_7512F2
			break;
		}
	}
}

//used to make tails actually do damage since unlike regular character he doesn't have code for
//this is mostly a port of sonic col damage

void Miles_DoCollisionAttackStuff(EntityData1* data1, CharObj2Base* co2) {

	CollisionInfo* col = data1->Collision;

	if (!col)
		return;

	CollisionData* colArray = col->CollisionArray;
	colArray->attr &= 0xFFFFBFFF;	unsigned int attrCol = colArray->attr;

	int colFlag1 = 0;
	int colFlag2 = 0;

	if (co2->Powerups >= 0)
	{
		if ((co2->Upgrades & Upgrades_SuperSonic) != 0)
		{
			colFlag1 = 3;
			colFlag2 = 3;
		}
		else
		{
			switch (data1->Action)
			{
			case LightDash:
				colFlag1 = 1;
				colFlag2 = 3;
				break;
			case Bounce:
				colFlag1 = 2;
				colFlag2 = 1;
				colArray->attr = attrCol | 0x4000;
				break;
			case Spinning:
				colArray[2].param1 = 10.0f;
				break;
			default:
				if ((data1->Status & Status_Attack) != 0)
				{
					colFlag1 = 1;
					colFlag2 = 1;
					if (data1->Action == Rolling)
					{
						colArray->attr = attrCol | 0x4000;
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
		if (data1->Action == Bounce)
		{
			colArray->attr = attrCol | 0x4000;
		}
	}

	colArray->damage = colArray->damage & 0xF0 | colFlag1 & 3 | (4 * (colFlag2 & 3));
	colArray[1].attr |= 0x10u;
}

void Miles_DisplayAfterImage(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3)
{
	if ((FrameCountIngame & 1) == 0 && a2->CharID == Characters_Tails && CharacterModels[208].Model)
	{
		NJS_OBJECT* obj = CharacterModels[208].Model;
		njPushMatrix(flt_25F02A0);

		njTranslateEx(&a1->Position);

		NJS_MATRIX_PTR matrix = _nj_current_matrix_ptr_;

		if (a1->Rotation.z)
		{
			njRotateZ((float*)_nj_current_matrix_ptr_, a1->Rotation.z);
		}
		if (a1->Rotation.x)
		{
			njRotateX(matrix, a1->Rotation.x);
		}
		if (a1->Rotation.y != 0x8000)
		{
			njRotateY(matrix, 0x8000 - a1->Rotation.y);
		}
		if (!TwoPlayerMode)
		{
			PlayerAfterImage(obj, 0, a3->TextureList, 0.0f, 0);
		}
		njPopMatrix(1u);
	}
}


void Miles_DrawTail(NJS_OBJECT* Tail, int(__cdecl* callback)(NJS_CNK_MODEL*)) {

	if (MilesCO2Extern) {

		char pNum = MilesCO2Extern->base.PlayerNum;
		char curAnim = MainCharObj2[pNum]->AnimInfo.Current;

		int model = MilesCO2Extern->base.AnimInfo.Animations[curAnim].ModelNum;

		if ((model == jmpBallID || isSA1Char(Characters_Tails) && model == 255 || isJumpBall && MainCharObj1[pNum]->Status & Status_Ball) || MainCharObj1[pNum]->Action == Rolling || isInTornado(pNum))
			return;

	}

	ProcessChunkModelsWithCallback(Tail, ProcessChunkModel);
}

//Many animations make Miles's tails in a very weird rotation, we force a specific rotation so they look decent here.
void CheckAndFixTailsRotation(CharObj2Base* co2, TailsCharObj2* co2Miles) {
	if (co2->AnimInfo.Current == 74 || co2->AnimInfo.Current >= 121 && co2->AnimInfo.Current <= 130 || co2->AnimInfo.Current >= 195 && co2->AnimInfo.Current <= 197)
		*(int*)&co2Miles->field_1BC[436] = -9000;
}

void LevelItem_r(ObjectMaster* tp)
{
	if (!MainCharObj2[0] || MainCharObj2[0]->CharID2 != Characters_Tails)
	{
		Levelitem_t.Original(tp);
	}
}

void init_Patches()
{
	WriteJump((void*)0x47A9C0, CheckAndSetPlayerSpeed); //make Miles bouncing when hitting enemy like other characters

	if (isCustomAnim) {
		WriteJump(reinterpret_cast<void*>(0x7512ea), CheckAnimateTailsAction); //fixes "static" Miles's Tails
	}

	//Draw the tails depending on the action
	WriteCall((void*)0x750B32, Miles_DrawTail);
	WriteCall((void*)0x750BB8, Miles_DrawTail);

	Levelitem_t.Hook(LevelItem_r);
}