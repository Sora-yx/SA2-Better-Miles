#include "pch.h"

void Miles_CheckSpinAttack(TailsCharObj2* co2M, EntityData1* twp, CharObj2Base* co2, EntityData2* a4)
{
	if (!isCustomAnim || CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7 || MilesCheckInput(a4, co2M, co2, twp) || Tails_CheckActionWindow_(twp, a4, co2, co2M)) {
		return;
	}

	if (Controllers[co2->PlayerNum].on & SpinBtn && (twp->Status & Status_OnPath) == 0)
	{

		twp->Action = (twp->Status & 3) ? Spinning : SpinningAir;
		twp->Status &= ~Status_Ball;
		co2->AnimInfo.Next = Spin1;
		co2->AnimInfo.field_8 = 0;
		co2M->field_3BC[122] |= 2u;
		PlaySoundProbably(8200, 0, 0, 0);
	}
}

void Miles_SpinAttack(playerwk* pwp, taskwk* twp, TailsCharObj2* mCO2)
{
	unsigned __int16 curAnim = pwp->mj.reqaction;
	char pnum = pwp->PlayerNum;

	if (curAnim >= Spin1 && curAnim <= Spin10)
	{
		AnimationIndex* sa2anim = getCharAnim_r();
		int curAnim = mCO2->base.AnimInfo.Current;
		int id = mCO2->base.AnimInfo.Animations[curAnim].AnimNum;
		AnimationIndex* plAct = &CharacterAnimations[id];

		if (sa2anim)
		{
			plAct = &sa2anim[id];
		}

		if (plAct->Animation->nbFrame - 10.0f >= pwp->mj.nframe)
		{
			TailsAnimationList_R[curAnim].NextAnimation = 0;
		}
		else if (Controllers[pwp->PlayerNum].on & SpinBtn)
		{

			if (GetAnalog((EntityData1*)twp, (CharObj2Base*)pwp, 0, 0))
			{
				unsigned __int16 nextAnim = ((((4096
					- (-njArcTan2((Controllers[pnum].y1 << 8), (Controllers[pnum].x1 << 8)))) >> 13) & 7) + Spin3);
				if (nextAnim == pwp->mj.reqaction)
				{
					TailsAnimationList_R[curAnim].NextAnimation = ((int)pwp->mj.nframe & 1) + Spin1;
				}
				else
				{
					TailsAnimationList_R[curAnim].NextAnimation = nextAnim;
					Play3DSound_Pos(8200, &twp->pos, 0, 0, 0);
				}

			}
			else
			{
				curAnim = pwp->mj.reqaction;
				if (curAnim == Spin1 || curAnim == Spin2)
				{
					TailsAnimationList_R[curAnim].NextAnimation = curAnim ^ 1;
					Play3DSound_Pos(8200, &twp->pos, 0, 0, 0);
				}
				else
				{
					TailsAnimationList_R[curAnim].NextAnimation = ((int)pwp->mj.nframe & 1) + Spin1;
				}
			}
		}
	}
}

void spinOnFrames(playerwk* pwk, EntityData1* data1, TailsCharObj2* mCo2)
{
	if (pwk->mj.reqaction) 
	{
		Miles_SpinAttack(pwk, (taskwk*)data1, mCo2);
	}
	else 
	{
		if (data1->Status & 3)
		{
			RestoreNextAnim();
			data1->Action = 1;
			pwk->mj.reqaction = 0;
		}
		else
		{
			RestoreNextAnim();
			data1->Action = 10;
			pwk->mj.reqaction = 15;
		}
	}
	return;
}

void spinLeaveGroundCheck(taskwk* twp, playerwk* pwp, TailsCharObj2* co2M)
{
	if (!(twp->flag & 3) || TailsJump((CharObj2Base*)pwp, (EntityData1*)twp))
	{
		twp->mode = SpinningAir;
		pwp->mj.reqaction = Spin1;
		twp->flag &= ~Status_Ball;
		return;
	}
}

void spinLandingCheck(taskwk* twp, playerwk* pwp)
{
	if (twp->flag & 3)
	{
		twp->mode = Spinning;
		pwp->mj.reqaction = Spin1;
		return;
	}
}

void Init_MilesSpin() {
	
	if (!isCustomAnim)
		return;

	WriteData<5>((void*)0x752567, 0x90); //Remove Tail Attack thing
	WriteData<3>((int*)0x751e56, 0x90);
	WriteData<11>((int*)0x74ed0a, 0x90);
	WriteData<5>((int*)0x74D7EE, 0x90);
}