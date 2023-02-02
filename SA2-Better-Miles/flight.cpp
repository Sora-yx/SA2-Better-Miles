#include "pch.h"

float TailsFlightTime = 0.0000000000f; //fatigue

void Tails_FlyStart(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3) { //rewrite the function to remove the vertical speed nerf since writedata doesn't work.

	a1->Action = Flying;
	a1->Status &= 0xDAFFu;
	a2->AnimInfo.Current = FlyingAnim;
	a3->field_3BC[122] |= 1u; //idk
	TailsFlightTime = 0.0f;

	if (!isTailsAI())
		PlayVoice(2, 1629);

	return;
}

static void __declspec(naked) Tails_FlyStartASM()
{
	__asm
	{
		push ecx
		push edx
		push eax
		call Tails_FlyStart
		add esp, 4
		pop edx
		pop ecx
		retn
	}
}


void PGetAccelerationFly(taskwk* twp, motionwk2* mwp, playerwk* pwp, TailsCharObj2* co2Tails)
{
	Angle diffAngleRes = 0;
	Angle angle = 0;
	NJS_POINT3 	acc = mwp->acc;
	Float stroke = 0.0f;
	Float flySPD = 0.0f;

	if (!co2Tails->field_3BC[120])
	{
		Play3DSound_EntityAndPos((EntityData1*)twp, 8201, &twp->pos, 60);
		co2Tails->field_3BC[120] = 1;
	}

	if ((twp->flag & Status_DisableControl) == 0)
	{

		Float weight = pwp->p.weight;
		acc.x += (weight * Gravity.x);
		acc.y += (weight * Gravity.y);
		acc.z += (weight * Gravity.z);
		PConvertVector_G2P((EntityData1*)twp, &acc);

		acc.x += (pwp->p.air_resist_air * pwp->spd.x);
		acc.y += (pwp->p.air_resist_y * pwp->spd.y);
		acc.z += (pwp->p.air_resist_z * pwp->spd.z);

		if (GetAnalog((EntityData1*)twp, (CharObj2Base*)pwp, &angle, &stroke))
		{
			Angle angAimY = angle;
			diffAngleRes = DiffAngle(twp->ang.y, angle);
			if (pwp->spd.x <= pwp->p.run_speed || diffAngleRes <= 24576)
			{
				mwp->ang_aim.y = angAimY;

				if (diffAngleRes <= 4096)
				{
					flySPD = (stroke * 0.1f);
					flySPD = ((stroke * 0.1f) * 1.5f);
				}
				else
				{
					flySPD = 0.0f;
				}
			}
			else
			{
				flySPD = (pwp->p.air_break * stroke);
			}

			PAdjustAngleY((EntityData1*)twp, (CharObj2Base*)pwp, mwp->ang_aim.y);
		}
		else
		{
			flySPD = 0.0f;
			mwp->ang_aim.y = twp->ang.y;
		}

		acc.x += flySPD;
		pwp->acc = acc;
	}
}

void MilesGetAccelerationFly(taskwk* twp, motionwk2* mwp, playerwk* pwp, TailsCharObj2* co2Tails)
{
	Uint8 pID = pwp->PlayerNum;

	if ((Controllers[pID].on & Buttons_A) != 0)
	{
		Float flyTime1 = (TailsFlightTime + 0.0063333338f); //0.0083333338f); sadx use 0.008 but this feel way too short in SA2

		if (flyTime1 > 1.0f)
			flyTime1 = 1.0f;

		TailsFlightTime = flyTime1;

		if (isInfiniteFly || flyTime1 < 1.0f)
		{

			if (pwp->spd.y >= 0.89999998f)
				mwp->acc.y += (1.0f - pwp->spd.y);
			else
				mwp->acc.y += 0.1f;

			PGetAccelerationFly(twp, mwp, pwp, co2Tails);
			return;
		}

		if (pwp->spd.y >= 0.0f)
		{
			PGetAccelerationFly(twp, mwp, pwp, co2Tails);
			return;
		}

		if (pwp->spd.y > -2.6500001f)
		{
			mwp->acc.y -= -((pwp->spd.y * 0.02f));
			PGetAccelerationFly(twp, mwp, pwp, co2Tails);
			return;
		}

		twp->flag = twp->flag & 0xFBFF;
		twp->mode = Action_Fall;
		pwp->mj.reqaction = 91;

		if (!isTailsAI())
			PlayCustomSoundVolume(Voice_TailsTired, 1);

		return;
	}
	else
	{
		if ((Action_Held[pID]) == 0)
		{
			if (pwp->spd.y >= -2.0f)
			{
				PGetAccelerationFly(twp, mwp, pwp, co2Tails);
				return;
			}

			mwp->acc.y = (((-2.0f - pwp->spd.y) * 0.1f) + mwp->acc.y);
			PGetAccelerationFly(twp, mwp, pwp, co2Tails);
			return;
		}

		Float limVSpdNeg = -pwp->p.lim_v_spd;

		if (pwp->spd.y <= limVSpdNeg)
			mwp->acc.y = ((limVSpdNeg - 0.1f) - pwp->spd.y) + mwp->acc.y;
		else
			mwp->acc.y = mwp->acc.y - 0.1f;

	}

	PGetAccelerationFly(twp, mwp, pwp, co2Tails);
}

void Miles_ManageFly(taskwk* twp, motionwk2* mwp, playerwk* pwp, TailsCharObj2* tailsCO2)
{
	EntityData1* data = (EntityData1*)twp;
	CharObj2Base* co2 = (CharObj2Base*)pwp;

	if (MilesCheckInput((EntityData2*)mwp, tailsCO2, co2, data) || Tails_CheckActionWindow_(data, (EntityData2*)mwp, co2, tailsCO2))
	{
		tailsCO2->field_3BC[122] &= 0xFEu;
	}
	else
	{

		if ((twp->flag & 3) != 0)
		{
			tailsCO2->field_3BC[122] &= 0xFEu;
			PlaySoundProbably(8195, 0, 0, 0);
			if (PlayerCheckBreak(0, data, co2) && pwp->spd.x > 0.0f)
			{
				twp->mode = 12;
				pwp->mj.reqaction = 18;
				pwp->mj.lastaction = 0;
				tailsCO2->field_3BC[128] = 0.80000001f;
				twp->flag &= 0xFBFFu;
			}
			else
			{

				twp->ang.x = mwp->ang_aim.x;
				if (PlayerStop(data, co2, (EntityData2*)mwp))
				{
					twp->ang.z = mwp->ang_aim.z;
					tailsCO2->field_3BC[128] = 0.80000001f;
					pwp->mj.reqaction = 1;
				}
				else
				{
					twp->mode = 1;
					twp->ang.z = mwp->ang_aim.z;
					PlayerChangeRunningMotion(co2, data);
					tailsCO2->field_3BC[128] = 0.80000001f;
				}

				twp->flag &= 0xFBFFu;
			}
		}
		else
		{
			if (isSuperForm(co2->PlayerNum) && co2->AnimInfo.Next == 92 || co2->AnimInfo.Current == 92)
			{
				co2->AnimInfo.Next = 15;
			}
		}
	}
}

void Init_MilesFly() {
	WriteJump((void*)0x752DB0, Tails_FlyStartASM); 	//Remove the altitude nerf.
	WriteJump((void*)0x752DF0, MilesGetAccelerationFly); //use SA1 flying code
}