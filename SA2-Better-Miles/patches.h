#pragma once


struct TailsCharObj2_
{
	CharObj2Base base;
	char field_1BC[40];
	NJS_POINT3 righthand_pos;
	NJS_POINT3 lefthand_pos;
	NJS_POINT3 rightfoot_pos;
	NJS_POINT3 leftfoot_pos;
	NJS_POINT3 head0_pos;
	NJS_POINT3 head1_pos;
	NJS_POINT3 head2_pos;
	NJS_POINT3 tailnode_pos;
	char field_2BC[36];
	NJS_POINT3 righthand_vec0;
	NJS_POINT3 lefthand_vec0;
	NJS_POINT3 righthand_vec1;
	NJS_POINT3 lefthand_vec1;
	NJS_POINT3 rightfoot_vec;
	NJS_POINT3 leftfoot_vec;
	NJS_POINT3 head0_vec;
	NJS_POINT3 head1_vec;
	NJS_POINT3 head2_vec;
	NJS_POINT3 tailnode_vec;
	char field_3BC[167];
	NJS_POINT3 tailVector0;
	NJS_POINT3 tailVector1;
	NJS_POINT3 tailVector2;
	NJS_TEXLIST* TextureList;
	ModelIndex* ModelList;
	AnimationIndex* MotionList;
	char field_5BC[36];
};


void Miles_DisplayAfterImage(EntityData1* a1, CharObj2Base* a2, TailsCharObj2* a3);
void SetSpacePhysics(CharObj2Base* co2);
void init_Patches();
void CheckAndSetHackObject(CharObj2Base* co2);
void UnloadLevelCharAnims();
void ReloadLevelCharAnims();