#include "stdafx.h"

//Setup a new animation list for Custom Animation. (Adding the SA1 ones mostly, but also extend the list to make Miles being able to use more actions such as Vine, Bar etc.)
AnimationInfo TailsAnimationList_R[] = {
	{ 95, 208, 3, 0, 0.0625f, 0.1f },
	{ 1, 208, 3, 1, 0.25f, 0.1f },
	//{ 95, 208, 3, 1, 0.25f, 0.1f },
	{ 95, 208, 3, 2, 0.25f, 0.1f },
	{ 95, 208, 4, 0, 0.25f, 0.1f },
	{ 4, 208, 3, 4, 0.03125f, 0.1f },
	{ 5, 208, 3, 5, 0.03125f, 0.1f },
	{ 96, 208, 11, 6, 0.25f, 3.4f },
	{ 113, 208, 11, 7, 0.25f, 1.4f },
	{ 114, 208, 11, 8, 0.25f, 1 },
	{ 97, 208, 11, 9, 0.25f, 1 },
	{ 97, 208, 10, 10, 0.25f, 1 },
	{ 11, 208, 11, 11, 0.25f, 0.4f },
	{ 12, 208, 10, 12, 0.25f, 0.7f },
	{ 13, 208, 3, 13, 0.25f, 0.4f },
	{ 14, 208, 4, 15, 0.125f, 0.3f },
	{ 15, 208, 3, 15, 0.25f, 0.4f },
	{ 115, 208, 4, 0, 1, 0.2f },
	{ 17, 208, 4, 0, 1, 0.4f },
	{ 18, 208, 9, 0, 0.25f, 0.3f },
	{ 19, 208, 4, 20, 0.125f, 0.2f },
	{ 20, 208, 3, 20, 0.25f, 0.6f },
	{ 21, 208, 6, 21, 1, 0.1f },
	{ 22, 208, 4, 1, 1, 1 },
	{ 23, 208, 3, 23, 0.0625f, 1 },
	{ 24, 208, 4, 25, 0.25f, 0.4f },
	{ 25, 208, 4, 0, 0.0625f, 0.3f },
	{ 26, 208, 4, 0, 0.0625f, 1 },
	{ 27, 208, 4, 0, 1, 1 },
	{ 28, 208, 3, 28, 0.0625f, 0.2f },
	{ 29, 208, 3, 29, 0.0625f, 0.2f },
	{ 30, 208, 3, 30, 0.5f, 1 },
	{ 99, 208, 4, 35, 0.5f, 0.3f },
	{ 117, 208, 11, 32, 0.5f, 1 },
	{ 33, 208, 4, 35, 0.5f, 1 },
	{ 34, 208, 4, 35, 0.5f, 1 },
	{ 100, 208, 3, 35, 0.5f, 0 },
	{ 36, 208, 3, 36, 0.03125f, 0 },
	{ 37, 208, 3, 37, 0.03125f, 0 },
	{ 116, 208, 11, 38, 0.5f, 1 },
	{ 39, 208, 4, 6, 0.5f, 0.5f },
	{ 40, 208, 3, 40, 0.5f, 0.6f },
	{ 41, 208, 3, 41, 0.5f, 0.4f },
	{ 103, 208, 3, 42, 0.5f, 0.3f },
	{ 43, 208, 4, 44, 0.5f, 0.2f },
	{ 44, 208, 3, 44, 0.5f, 0.1f },
	{ 45, 208, 3, 45, 0.5f, 0.1f },
	{ 46, 208, 4, 47, 0.5f, 0.1f },
	{ 47, 208, 3, 47, 0.5f, 0.3f },
	{ 112, 208, 4, 35, 0.5f, 0.2f },
	{ 49, 208, 4, 0, 0.5f, 0.3f },
	{ 50, 208, 4, 0, 0.5f, 0.3f },
	{ 51, 208, 4, 15, 0.5f, 0.3f },
	{ 52, 208, 4, 15, 0.5f, 0.3f },
	{ 99, 208, 7, 0, 1, 0.3f },
	{ 98, 208, 6, 54, 0.5f, 1 },
	{ 55, 208, 3, 55, 0.125f, 0.3f },
	{ 56, 208, 4, 15, 1, 0.25f },
	{ 57, 208, 4, 58, 0.125f, 0.1f },
	{ 58, 208, 3, 58, 1, 0.1f },
	{ 59, 208, 6, 59, 1, 0.2f },
	{ 60, 208, 6, 60, 0.25f, 1 },
	{ 61, 208, 4, 0, 0.25f, 4 },
	{ 109, 208, 6, 62, 0.25f, 0.1f },
	{ 110, 208, 4, 0, 0.25f, 0.3f },
	{ 111, 208, 4, 0, 0.25f, 0.3f },
	{ 65, 208, 4, 66, 0.25f, 1.4f },
	{ 66, 208, 3, 66, 0.25f, 1 },
	{ 107, 208, 4, 68, 0.125f, 0.4f },
	{ 108, 208, 3, 68, 0.125f, 0.4f },
	{ 69, 208, 4, 70, 0.25f, 0.1f },
	{ 70, 208, 3, 70, 1, 0.2f },
	{ 71, 208, 9, 0, 0.125f, 0.2f },
	{ 72, 208, 6, 72, 0.25f, 0.2f },
	{ 73, 208, 4, 0, 0.25f, 0.3f },
	{ 74, 208, 3, 74, 0.25f, 0.4f },
	{ 75, 208, 3, 75, 0.25f, 0.1f },
	{ 76, 208, 6, 76, 0.25f, 0.3f },
	{ 77, 208, 3, 77, 0.25f, 0.8f },
	{ 104, 208, 3, 78, 0.125f, 0.2f },
	{ 79, 208, 4, 0, 0.25f, 0.3f },
	{ 80, 208, 5, 81, 0.25f, 0.5f },
	{ 81, 208, 4, 0, 0.25f, 0.5f },
	{ 82, 208, 9, 0, 0.25f, 0.5f },
	{ 83, 208, 4, 0, 0.0625f, 0.15f },
	{ 84, 208, 4, 0, 0.0625f, 0.15f },
	{ 85, 208, 6, 85, 0.25f, 0.1f },
	{ 86, 208, 3, 86, 1, 0.5f },
	{ 87, 208, 3, 87, 0.03125f, 0.1f },
	{ 88, 208, 3, 88, 0.03125f, 0.1f },
	{ 89, 208, 7, 0, 0.25f, 0.25f },
	{ FlyingAnim, 208, 3, 90, 0.0625f, 0.1f },
	{ 91, 208, 4, 92, 0.25f, 0.1f },
	{ 92, 208, 3, 92, 0.25f, 0.1f },
	{ 93, 208, 6, 93, 0.25f, 0.1f },
	{ 94, 208, 4, 0, 0.125f, 1 },
	{ 95, 208, 3, 95, 0.0625f, 0.1f },
	{ 96, 208, 11, 96, 0.25f, 3.4f },
	{ 97, 208, 10, 97, 0.25f, 1 },
	{ 98, 208, 6, 98, 0.5f, 1 },
	{ 99, 208, 4, 100, 0.5f, 1 },
	{ 100, 208, 3, 100, 0.5f, 0 },
	{ 101, 208, 4, 70, 0.25f, 0.1f },
	{ 102, 208, 8, 102, 1, 0.1f },
	{ 103, 208, 3, 103, 0.5f, 0.5f },
	{ 104, 208, 3, 104, 0.125f, 0.2f },
	{ 105, 208, 4, 66, 0.25f, 0.4f },
	{ 106, 208, 3, 66, 0.25f, 0.4f },
	{ 107, 208, 4, 68, 0.125f, 0.4f },
	{ 108, 208, 3, 68, 0.125f, 0.4f },
	{ 109, 208, 6, 109, 0.25f, 0.1f },
	{ 110, 208, 4, 0, 0.25f, 0.3f },
	{ 111, 208, 4, 0, 0.25f, 0.3f },
	{ 112, 208, 4, 0, 1, 0.3f },
	{ 113, 208, 11, 0, 0.25f, 0.3f },
	{ 114, 208, 11, 0, 0.25f, 0.3f },
	{ 115, 208, 4, 0, 1, 0.3f },
	{ 116, 208, 11, 0, 0.25f, 0.3f },
	{ 117, 208, 11, 0, 0.25f, 0.3f },
	//SA1 Anim
	{ VictoryAnim, 208, 6, 119, 0.5f, 0.7F },
	{ VictoryPoseEnd, 208, 6, 0, 0.5f, 1 },
	{ Spin1, 208, 4, 0, 0.125f, 1 },
	{ Spin2, 208, 4, 0, 0.125f, 1 },
	{ Spin3, 208, 4, 0, 0.125f, 1 },
	{ Spin4, 208, 4, 0, 0.125f, 1 },
	{ Spin5, 208, 4, 0, 0.125f, 1 },
	{ Spin1, 208, 4, 0, 0.125f, 1 },
	{ Spin7, 208, 4, 0, 0.125f, 1 },
	{ Spin8, 208, 4, 0, 0.125f, 1 },
	{ Spin1, 208, 4, 0, 0.125f, 1 },
	{ Spin10, 208, 4, 0, 0.125f, 1 },
	{ Spin10, 208, 4, 0, 0.125f, 1 },
	//Extended
	{ 132, 208, 4, 121, 0.25f, 0.3f },
	{ 131, 208, 4, 122, 0.25f, 0.3f },
	{ 133, 208, 4, 130, 1, 1 },
	{ 134, 208, 4, 130, 1, 1 },
	{ 135, 208, 4, 130, 0.0625f, 1.25f },
	{ 136, 208, 4, 130, 0.0625f, 1 },
	{ 137, 208, 4, 130, 1, 1 },
	{ 138, 208, 4, 130, 0.0625f, 1.25f },
	{ 139, 208, 4, 130, 1, 1 },
	{ 140, 208, 4, 130, 1, 1 },
	{ 141, 208, 4, 130, 0.0625f, 1.25f },
	{ 142, 208, 4, 130, 0.0625f, 1.25f },
	{ 143, 208, 4, 130, 1, 1 },
	{ 144, 208, 4, 130, 0.0625f, 1 },
	{ 145, 208, 13, 121, 0.25f, 0.3f },
	{ 146, 208, 13, 122, 0.25f, 0.3f },
	{ 147, 208, 13, 123, 0.25f, 0.3f },
	{ 148, 208, 13, 124, 0.25f, 0.3f },
	{ 149, 208, 3, 125, 0.25f, 0.3f },
	{ 150, 208, 3, 126, 0.25f, 0.3f },
	{ 151, 208, 6, 127, 0.25f, 0.4f },
	{ 152, 208, 4, 129, 0.125f, 0.3f },
	{ 153, 208, 3, 129, 0.125f, 0.4f },
	{ 154, 208, 4, 121, 0.125f, 0.4f },
	{ 156, 208, 4, 121, 0.25f, 0.3f },
	{ 155, 208, 4, 122, 0.25f, 0.3f },
	{ 157, 208, 9, 129, 0.0625f, 1 },
	{ 158, 208, 9, 129, 0.0625f, 1 },
	{ 159, 208, 9, 129, 0.0625f, 1 },
	{ 160, 208, 9, 129, 0.0625f, 1 },
	{ 161, 208, 9, 129, 0.0625f, 1 },
	{ 162, 208, 9, 129, 0.0625f, 1 },
	{ 163, 208, 9, 129, 0.0625f, 1 },
	{ 164, 208, 9, 129, 0.0625f, 1 },
	{ 165, 208, 9, 129, 0.0625f, 1 },
	{ 166, 208, 9, 129, 0.0625f, 1 },
	{ 167, 208, 9, 129, 0.0625f, 1 },
	{ 168, 208, 9, 129, 0.0625f, 1 },
	{ 169, 208, 3, 169, 0.0625f, 0.1f },
	{ 170, 208, 3, 170, 0.25f, 0.1f },
	{ 171, 208, 11, 171, 0.25f, 1.4f },
	{ 172, 208, 11, 172, 0.25f, 1.4f },
	{ 173, 208, 11, 173, 0.25f, 1.4f },
	{ 174, 208, 11, 174, 0.25f, 1.4f },
	{ 175, 208, 4, 169, 0.25f, 1.4f },
	{ 176, 208, 3, 176, 0.03125f, 0.1f },
	{ 177, 208, 3, 177, 0.03125f, 0.1f },
	{ 178, 208, 9, 0, 0.03125f, 0.25f },
	{ 179, 208, 4, 169, 0.25f, 1.4f },
	{ 180, 208, 6, 180, 0.25f, 1.4f },
	{ 181, 208, 6, 181, 0.25f, 1.4f },
	{ 182, 208, 6, 182, 1, 1 },
	{ 183, 208, 6, 183, 1, 1 },
	{ 184, 208, 3, 184, 1, 0.5f },
	{ 185, 208, 4, 186, 0.25f, 0.3f },
	{ 186, 208, 3, 186, 0.25f, 0.5f },
	{ 187, 208, 3, 187, 0.25f, 0.8f },
	{ 188, 208, 6, 188, 0.25f, 0.3f },
	{ 189, 208, 4, 189, 0.25f, 0.2f },
	{ 190, 208, 3, 190, 0.25f, 0.3f },
	{ 191, 208, 3, 191, 0.25f, 0.2f },
	{ 192, 208, 11, 192, 0.25f, 0.2f },
	{ 193, 208, 11, 192, 0.25f, 0.2f },
	{ 194, 208, 3, 194, 0.0625f, 0.2f },
	{ 195, 208, 3, 195, 0.0625f, 0.2f },
	{ 196, 208, 3, 196, 0.0625f, 0.2f },
	{ 197, 208, 3, 197, 0.0625f, 0.2f },
	{ 198, 208, 3, 198, 0.125f, 0.2f },
	{ 199, 208, 3, 199, 0.25f, 0.2f },
	{ 200, 208, 3, 200, 0.25f, 0.2f },
	{ 201, 208, 6, 201, 0.125f, 0.8f },
	{ 202, 208, 3, 202, 0.125f, 0.5f },
	//grinding + tricks
	{ 203, 208, 13, 104, 0.25f, 0.3f },
	{ 204, 208, 13, 105, 0.25f, 0.3f },
	{ 205, 208, 13, 106, 0.25f, 0.3f },
	{ 206, 208, 13, 107, 0.25f, 0.3f },
	{ 207, 208, 13, 108, 0.25f, 0.3f },
	{ 208, 208, 13, 109, 0.25f, 0.3f },
	{ 209, 208, 13, 110, 0.25f, 0.3f },
	{ 210, 208, 13, 111, 0.25f, 0.3f },
	{ 211, 208, 3, 112, 0.25f, 0.3f },
	{ 212, 208, 3, 113, 0.25f, 0.3f },
	{ 213, 208, 9, 15, 0.0625f, 0.2f },
	{ 214, 208, 4, 15, 0.0625f, 0.35f },
	{ 215, 208, 4, 15, 0.0625f, 0.35f },
	//Super Sonic Imported anim (intro + victory pose)
	{ 216, 208, 4, 87, 1, 0.5f }, 
	{ 217, 208, 6, 101, 1, 0.5f },
};



void FixAnimationFinalBossOnFrames(CharObj2Base* co2, EntityData1* data1) {

	if (CurrentLevel == LevelIDs_FinalHazard && data1->NextAction == 0) {

		if (co2->AnimInfo.Next == 100 || co2->AnimInfo.Current == 100)
		{
			if (!isCustomAnim)
				co2->AnimInfo.Next = 66;
			else
				co2->AnimInfo.Next = 216;
		}
		else if (co2->AnimInfo.Current == 216)
		{
			if (!data1->Status & Status_DisableControl) {
				data1->Action = 59;
				co2->AnimInfo.Next = 15;
			}
		}
		else {
			data1->Action = 59;
			co2->AnimInfo.Next = 15;
		}
	}
}



void Init_NewAnimation() {
	WriteData((AnimationInfo**)0x74CFD7, TailsAnimationList_R);
}
