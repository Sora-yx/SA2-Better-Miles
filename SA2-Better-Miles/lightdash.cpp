#include "pch.h"

int lightdashTime = 0;
int lightdashTimer = 0;

void resetLightdashTimer()
{
	lightdashTime = 0;
	lightdashTimer = 0;
}
Trampoline* RingMain_t = nullptr;
NJS_VECTOR LightDashPos = { 0 };

void Miles_PerformLightDash(CharObj2Base* co2, EntityData1* data)
{
	data->Action = LightDash;
	if (isCustomAnim)
		co2->AnimInfo.Next = LightdashAnim;
	else
		co2->AnimInfo.Next = 4;
	lightdashTime = 10;
	lightdashTimer = 0;
	co2->Speed.x = 16.0f;
	data->Status = data->Status & ~Status_Ball | Status_Attack;
	PlaySoundProbably(8210, 0, 0, 0);
}


void CheckLightDashEnd(TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData1* data1)
{
	int lightdashTimee = lightdashTime;
	int getTimer = lightdashTimee - 1;
	lightdashTime = lightdashTimee - 1;
	NJS_VECTOR vecIDK{ 0 };

	if (lightdashTimee > 0)
	{
		if (++lightdashTimer <= 360)
		{
			CollisionInfo* col = (CollisionInfo*)data1->Collision->CollidingObject;
			if (col)
			{
				ObjectMaster* idkOBJ = col->Object;

				if (idkOBJ)
				{
					char IDThing = idkOBJ->Data1.Entity->field_2;
					if (IDThing == 21)
					{
						data1->Action = 10;
						co2->AnimInfo.Next = 15;
						co2->Speed.y = 0.0f;
						lightdashTime = 0;
						data1->Status &= 0xFBFFu;
						//PlaySound3(-1025, 8210);
						return;
					}
					if (IDThing == 17)
					{
						if (lightdashTimer <= 0)
						{
							lightdashTimer++;
						}
					}
				}
			}

			return;
		}
	}

	data1->Action = 10;
	co2->AnimInfo.Next = 15;

	NJS_VECTOR* spd = &co2->Speed;

	if (sub_45B2C0(co2, 0, data1) < 2 || lightdashTimer <= 1)
	{
		if (njScalor(spd) > 2.0f)
		{
			njUnitVector(spd);
			co2->Speed.x *= 4.0f;
			co2->Speed.y *= 4.0f;
			co2->Speed.z *= 4.0f;
		}
	}
	else
	{
		player_parameter* physics = (player_parameter*)&co2->PhysData;
		co2->Speed.x = physics->jmp_addit;
		if (njScalor(spd) > 0.0f)
		{
			njUnitVector(spd);
			co2->Speed.x *= physics->jmp_addit + 1.0f;
			co2->Speed.y *= physics->jmp_addit + 1.0f;
			co2->Speed.z *= physics->jmp_addit * 2.0f;
		}
	}

	lightdashTime = 0;
	data1->Status &= 0xFBFFu;
}


void CheckRefreshLightDashTimer(CharObj2Base* pwp, EntityData1* twp, motionwk2* mwp)
{
	HomingAttackTarget* ring_list = ring_list = around_ring_list_p0;

	if (pwp->PlayerNum)
		ring_list = around_ring_list_p1;

	if (ring_list->entity)
	{
		NJS_VECTOR vd = { 1.0f, 0.0f, 0.0f };
		PConvertVector_P2G(twp, &vd);
		njUnitVector(&vd);
		taskwk* ringtwp = (taskwk*)ring_list->entity;
		taskwk* ringtwp2 = 0;
		if (ring_list->entity)
		{
			Float dist = 0;
			NJS_VECTOR ringpos;
			do
			{
				ringpos = ringtwp->pos;
				njAddVector(&ringpos, &ringtwp->cwp->info->center);
				njSubVector(&ringpos, &twp->Position);
				Float vd_sqrt = njSqrt(ringpos.y * ringpos.y + ringpos.z * ringpos.z + ringpos.x * ringpos.x);
				if (vd_sqrt == 0.0f)
				{
					ringpos = { 0.0f, 0.0f, 0.0f };
				}
				else
				{
					Float div = 1.0f / vd_sqrt;
					ringpos.x *= div;
					ringpos.y *= div;
					ringpos.z *= div;
				}
				if (VectorAngle(0, &vd, &ringpos) <= 0x3000 && (!ringtwp2 || ring_list->distance < dist))
				{
					ringtwp2 = ringtwp;
					dist = ring_list->distance;
				}
				ringtwp = (taskwk*)ring_list[1].entity;
				++ring_list;
			} while (ringtwp);

			if (ringtwp2)
			{
				if (lightdashTime < 5)
				{
					lightdashTime = 5;
				}
				ringpos = ringtwp2->pos;
				njAddVector(&ringpos, &ringtwp2->cwp->info->center);
				njSubVector(&ringpos, &twp->Position);
				twp->Rotation.y = AdjustAngle(twp->Rotation.y, njArcTan2(ringpos.z, ringpos.x), 0x1800);
				mwp->ang_aim.y = twp->Rotation.y;
				Float dist_sqrt = njSqrt(dist);
				if (dist_sqrt <= 16.0f)
				{
					if (dist_sqrt < 2.0f)
					{
						dist_sqrt = 2.0f;
					}
				}
				else
				{
					dist_sqrt = 16.0f;
				}
				if (njScalor(&ringpos) <= 1.0f)
				{
					ringpos = mwp->spd;
				}
				njUnitVector(&ringpos);
				mwp->spd.x = ringpos.x * dist_sqrt;
				mwp->spd.y = ringpos.y * dist_sqrt;
				mwp->spd.z = ringpos.z * dist_sqrt;
				PConvertVector_G2P(twp, &ringpos);
				pwp->Speed = ringpos;
			}
		}
	}
	else
	{
		if (lightdashTimer <= 1 && !sub_721480(pwp, twp, 64.0f))
		{
			if (njScalor(&pwp->Speed) > 2.0f)
			{
				njUnitVector(&pwp->Speed);
				pwp->Speed.x *= 2.0f;
				pwp->Speed.y *= 2.0f;
				pwp->Speed.z *= 2.0;
			}
			lightdashTime = 0;
		}
		PGetInertia(twp, (EntityData2*)mwp, pwp);
		PGetSpeed(twp, pwp, (EntityData2*)mwp);
	}
}

void Check_LightDash(taskwk* twp, CharObj2Base* pwp)
{
	if (!isLightDash || twp->flag & Status_HoldObject || twp->mode > Flying)
		return;

	if (sub_721480(pwp, (EntityData1*)twp, 35.0f))
		pwp->ActionWindowItems[pwp->ActionWindowItemCount++ & 7] = LightDash;
}