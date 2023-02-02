#include "pch.h"

NJS_MATRIX TailsMatrix1;
NJS_MATRIX TailsMatrix2;
NJS_MATRIX InstanceMatrices[128];

int FailSafeTimer = 0;
int spinDelay = 0;
Uint32 LastModelIndex;

Uint32 matctr;

//port all the SA1 calc matrix stuff to make the cool tails effects working

/*
*	Custom, could do with a union or something.
*/
typedef struct NJS_MKEY_P_F
{
	Uint32 keyframe;
	NJS_MKEY_F* key;
}NJS_MKEY_P_F;

typedef struct SMMparams 
{
	void* mot;
	NJS_MATRIX* mbp;
	int type;
	int motfrm;
	float frm;
} SMMparams;

void njGetMatrix(NJS_MATRIX_PTR m)
{
	njSetMatrix(m, _nj_current_matrix_ptr_);
}


Angle SubAngle(Angle ang0, Angle ang1)
{
	return (Sint16)(ang1 - ang0);
}

NJS_OBJECT* ScanMotionModel(NJS_OBJECT* obj, SMMparams* smmpp)
{
	Sint32 flag3;
	Sint32 type;
	NJS_MKEY_P_F mkey_p;
	NJS_MKEY_F* mkey_f;
	NJS_MKEY_A* mkey_a;
	NJS_MKEY_F* current_mot;
	Float frame;
	Float* position;
	Angle* angle;
	Float* scale;
	NJS_MDATA2* mdata2;
	NJS_MDATA3* mdata3;

	if (++matctr <= LastModelIndex)
	{
		//Check if MDATA2 or MDATA3
		type = smmpp->type;
		flag3 = 1;
		Sint32 mdata_type = 0;
		for (mdata_type = 0; mdata_type < 5; mdata_type++) {
			if (!type)
			{
				break;
			}
			type &= ~flag3;
			flag3 *= 2;
		}
		njPushMatrix(0);
		switch (mdata_type) {
		case 2:
			//MDATA2
			mdata2 = (NJS_MDATA2*)smmpp->mot;
			for (Sint32 i = 0; i < 2; i++) {
				current_mot = (NJS_MKEY_F*)mdata2->p[i];
				if (current_mot)
				{
					mkey_p.keyframe = (Uint32)smmpp->frm;
					mkey_p.key = &current_mot[1];
					mkey_f = (NJS_MKEY_F*)mdata2->p[i];
					while (mkey_p.keyframe > mkey_f->keyframe)
					{
						if (mkey_p.keyframe < mkey_p.key->keyframe)
						{
							break;
						}
						++mkey_f;
						++mkey_p.key;
					};
					mkey_p.keyframe = mkey_f->keyframe;
					if (mkey_f->keyframe == smmpp->motfrm - 1)
					{
						mkey_p.key = (NJS_MKEY_F*)mdata2->p[i];
						frame = smmpp->frm - (Float)mkey_p.keyframe;
					}
					else
					{
						frame = (smmpp->frm - (Float)mkey_p.keyframe) / ((Float)mkey_p.key->keyframe - mkey_p.keyframe);
					}
					switch (i) {
					case 0:
					default:
						position = ((NJS_MKEY_F*)(mkey_p.key))->key;
						njTranslate(0,
							(position[0] - mkey_f->key[0]) * frame + mkey_f->key[0],
							(position[1] - mkey_f->key[1]) * frame + mkey_f->key[1],
							(position[2] - mkey_f->key[2]) * frame + mkey_f->key[2]);
						break;
					case 1:
						angle = ((NJS_MKEY_A*)(mkey_p.key))->key;
						mkey_a = (NJS_MKEY_A*)mkey_f;
						njRotateXYZ(0,
							mkey_a->key[0] + (Sint32)((Float)SubAngle(mkey_a->key[0], angle[0]) * frame),
							mkey_a->key[1] + (Sint32)((Float)SubAngle(mkey_a->key[1], angle[1]) * frame),
							mkey_a->key[2] + (Sint32)((Float)SubAngle(mkey_a->key[2], angle[2]) * frame));
						break;
					}
				}
				else {
					switch (i) {
					case 0:
					default:
						if (!(obj->evalflags & NJD_EVAL_UNIT_POS))
						{
							njTranslateV(0, (NJS_VECTOR*)obj->pos);
						}
						break;
					case 1:
						if (!(obj->evalflags & NJD_EVAL_UNIT_ANG))
						{
							njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
						}
						break;
					}
				}
			}
			if (!(obj->evalflags & 4)) //Not NOSCALE
			{
				njScale_(obj->scl[0], obj->scl[1], obj->scl[2]);
			}
			smmpp->mot = &mdata2[1];
			break;
		case 3:
			//MDATA3
			mdata3 = (NJS_MDATA3*)smmpp->mot;
			for (Sint32 i = 0; i < 3; i++) {
				current_mot = (NJS_MKEY_F*)mdata3->p[i];

				if (current_mot)
				{
					mkey_p.keyframe = (Uint32)smmpp->frm;
					mkey_p.key = &current_mot[1];
					mkey_f = (NJS_MKEY_F*)mdata3->p[i];
					if (mkey_p.keyframe > current_mot->keyframe)
					{
						do
						{
							if (mkey_p.keyframe < mkey_p.key->keyframe)
							{
								break;
							}
							++mkey_f;
							++mkey_p.key;
						} while (mkey_p.keyframe > mkey_f->keyframe);
					}

					mkey_p.keyframe = mkey_f->keyframe;

					if (mkey_f->keyframe == smmpp->motfrm - 1)
					{
						mkey_p.key = (NJS_MKEY_F*)mdata3->p[i];
						frame = smmpp->frm - mkey_p.keyframe;
					}
					else
					{
						frame = (smmpp->frm - mkey_p.keyframe) / (mkey_p.key->keyframe - mkey_p.keyframe);
					}

					switch (i) {
					case 0:
					default:
						position = ((NJS_MKEY_F*)(mkey_p.key))->key;
						njTranslate(0,
							(position[0] - mkey_f->key[0]) * frame + mkey_f->key[0],
							(position[1] - mkey_f->key[1]) * frame + mkey_f->key[1],
							(position[2] - mkey_f->key[2]) * frame + mkey_f->key[2]);
						break;
					case 1:
						angle = ((NJS_MKEY_A*)(mkey_p.key))->key;
						mkey_a = (NJS_MKEY_A*)mkey_f;
						njRotateXYZ(0,
							mkey_a->key[0] + (Sint32)((Float)SubAngle(mkey_a->key[0], angle[0]) * frame),
							mkey_a->key[1] + (Sint32)((Float)SubAngle(mkey_a->key[1], angle[1]) * frame),
							mkey_a->key[2] + (Sint32)((Float)SubAngle(mkey_a->key[2], angle[2]) * frame));
						break;
					case 2:
						scale = ((NJS_MKEY_F*)(mkey_p.key))->key;
						njScale(0,
							(scale[0] - mkey_f->key[0]) * frame + mkey_f->key[0],
							(scale[1] - mkey_f->key[1]) * frame + mkey_f->key[1],
							(scale[2] - mkey_f->key[2]) * frame + mkey_f->key[2]);
						break;
					}
				}
				else {
					switch (i) {
					case 0:
					default:
						if (!(obj->evalflags & NJD_EVAL_UNIT_POS))
						{
							njTranslateV(0, (NJS_VECTOR*)obj->pos);
						}
						break;
					case 1:
						if (!(obj->evalflags & NJD_EVAL_UNIT_ANG))
						{
							njRotateXYZ(0, obj->ang[0], obj->ang[1], obj->ang[2]);
						}
						break;
					case 2:
						if (!(obj->evalflags & NJD_EVAL_UNIT_SCL))
						{
							njScale_(obj->scl[0], obj->scl[1], obj->scl[2]);
						}
						break;
					}
				}
			}
			smmpp->mot = &mdata3[1]; //Next
			break;
		default:
			while (1)
			{
				//Crash the game if not MDATA2 or MDATA3.
				;
			}
			break;
		}

		njGetMatrix((NJS_MATRIX_PTR)smmpp->mbp);
		++smmpp->mbp;
		for (NJS_OBJECT* i = obj->child; i; i = ScanMotionModel(i, smmpp))
		{
			;
		}
		njPopMatrix(1);
		return obj->sibling;
	}
	else
	{
		matctr = LastModelIndex;
		return NULL;
	}
}

Bool CalcMMMatrix(NJS_MATRIX_PTR inpmat, NJS_ACTION* actptr, Float motfrm, Uint32 srcnmb, NJS_MATRIX_PTR ansmat)
{
	SMMparams params;
	matctr = 0;
	LastModelIndex = srcnmb + 1;
	if (LastModelIndex > 0x80)
	{
		LastModelIndex = 0x80;
	}
	njPushMatrix(0);
	if (inpmat)
	{
		njSetMatrix(0, inpmat);
	}
	NJS_OBJECT* object = actptr->object;
	NJS_MOTION* motion = actptr->motion;
	params.mot = motion->mdata;
	params.mbp = InstanceMatrices;
	params.type = motion->type;
	params.motfrm = motion->nbFrame;
	params.frm = motfrm - (Float)(motion->nbFrame * ((Uint32)motfrm / motion->nbFrame));
	ScanMotionModel(object, &params);
	if (ansmat)
	{
		njSetMatrix(ansmat, InstanceMatrices[srcnmb]);
	}
	njPopMatrix(1);
	return TRUE;
}