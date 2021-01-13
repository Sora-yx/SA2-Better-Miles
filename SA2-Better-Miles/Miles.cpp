#include "stdafx.h"
#include <fstream>
#include <iostream>

Trampoline* Tails_Main_t = nullptr;
Trampoline* Miles_CheckNextActions_t = nullptr;
AnimationIndex newTailsAnimIndex[130];

//Setup a new animation list for Custom Animation (adding the SA1 ones mostly)
AnimationInfo TailsAnimationList_R[] = {
	{ 95, 208, 3, 0, 0.0625f, 0.1f },
	{ 95, 208, 3, 1, 0.25f, 0.1f },
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
	{ 105, 208, 4, 66, 0.25f, 0.4f },
	{ 106, 208, 3, 66, 0.25f, 0.1f },
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
	{ RollAnim, 208, 10, RollAnim, 0.25f, 0.40000001 },
};


//Trampoline Usercall Function to get the control of "Check Next Actions" this need 3 functions to work.
static const void* const Miles_CheckNextActionPtr = (void*)0x751CB0;
signed int Miles_CheckNextActions_original(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

	const auto MilesCheck_ptr = Miles_CheckNextActions_t->Target();

	signed int result;

	__asm
	{
		mov esi, a4 // a4
		mov edi, a3 // a3
		mov ebx, a2 // a2
		mov ecx, a1 // a1

		// Call your __cdecl function here:
		call MilesCheck_ptr

		mov result, eax
	}

	return result;

}
signed int __cdecl Miles_CheckNextActions_r(EntityData2_* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4) {

	if (a4->NextAction == 20)
	{
		a4->Action = Pulley;
		a3->AnimInfo.Next = 75;
		return 1;
	}

	return Miles_CheckNextActions_original(a1, a2, a3, a4);
}


static void __declspec(naked) Miles_CheckNextActionsASM()
{

	__asm
	{
		push esi // a4
		push edi // a3
		push ebx // a2
		push ecx // a1

		// Call your __cdecl function here:
		call Miles_CheckNextActions_r

		pop ecx // a1
		pop ebx // a2
		pop edi // a3
		pop esi // a4
		retn
	}
}



//Jump to a specific address where the game will call the function to animate Miles's tails
static const void* const loc_74D34C = (void*)0x74D34C;
__declspec(naked) void GoToAnimatedTailAnimation()
{
	__asm jmp loc_74D34C
}


//Rework the condition to add the victory pose
static const void* const loc_7512F2 = (void*)0x7512F2;
__declspec(naked) void  CheckVictoryPose() {

	if (MainCharObj1[0]->Action != 24 || MainCharObj1[0]->Action != VictoryPose)
	{
		_asm jmp loc_7512F2
	}
}


static const void* const TailsJumpPtr = (void*)0x751B80;
inline int Tails_JumpStart(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		push[a1]
		mov eax, [a1]
		// Call your __cdecl function here:
		call TailsJumpPtr
		mov result, eax
		add esp, 4 // a1<eax> is also used for return value
		pop ecx // a2
	}

	return result;
}


void Tails_Main_r(ObjectMaster* obj)
{
	ObjectFunc(origin, Tails_Main_t->Target());
	origin(obj);

	CharObj2Base* co2 = MainCharObj2[0];
	EntityData1* data1 = MainCharObj1[0];
	EntityData2_* data2 = EntityData2Ptrs[0];
	TailsCharObj2* co2Miles = (TailsCharObj2*)MainCharObj2[0];


	switch (data1->Action)
	{
	case Standing:
	case Running:
		if (!isCustomAnim || CurrentLevel == LevelIDs_ChaoWorld && CurrentChaoArea != 7)
			return;

		if (co2->Speed.x < 1.3)  {
			Miles_CheckSpinAttack(data1, co2);	
		}
		else {
			//Miles_RollCheckInput(data1, co2);
		}
		break;
	case Jumping:

		break;
	case ObjectControl:
		if (!isCustomAnim)
			return;

		if (TimerStopped != 0) { //Check if the level is finished
			co2->field_28 = VictoryAnim;
			co2->AnimInfo.Next = VictoryAnim;
			data1->Action = VictoryPose; //SA2 spams the animation 54 every frame, so we force the game to an action which doesn't exist so we can play the animation needed.
		}
		break;
	case Pulley:
		//Miles_CheckNextActionsASM(data2, co2Miles, co2, data1);
		if (data1->NextAction == 0) {
			Tails_JumpStart(co2, data1);
		}

		break;
	case Spinning:
		if (isCustomAnim)
			spinOnFrames(co2, data1);
		break;
	case VictoryPose:
		co2->AnimInfo.Current = VictoryAnim;
		GoToAnimatedTailAnimation();
		break;
	case Rolling:
		Miles_UnrollCheckInput(data1, co2);
		break;
	}

	MilesFly(data1, co2, data2);
}


void LoadCharacterAndNewAnimation() {
	PDS_PERIPHERAL p1 = Controllers[0];

	//if (p1.press & Buttons_Y || p1.on & Buttons_Y || p1.release & Buttons_Y)
		CurrentCharacter = Characters_Tails;

	LoadCharacters();

	if (MainCharObj2[0]->CharID != Characters_Tails)
		return;

	if (isCustomAnim) {
		MainCharObj2[0]->AnimInfo.Animations = TailsAnimationList_R;
	}
}


void BetterMiles_Init() {
	Tails_Main_t = new Trampoline((int)Tails_Main, (int)Tails_Main + 0x6, Tails_Main_r);
	Miles_CheckNextActions_t = new Trampoline(0x751CB0, 0x751CB5, Miles_CheckNextActionsASM);

	//Improve physic
	PhysicsArray[Characters_Tails].AirAccel = 0.050;
	PhysicsArray[Characters_Tails].Brake = -0.25;
	PhysicsArray[Characters_Tails].HangTime = 60;
	PhysicsArray[Characters_Tails].JumpSpeed = 1.80;
	PhysicsArray[Characters_Tails].GroundAccel = 0.14;

	MilesFly_Init();

	//Custom anim + Force Load Tails Check
	WriteCall((void*)0x439b13, LoadCharacterAndNewAnimation);
	WriteCall((void*)0x43cada, LoadCharacterAndNewAnimation);

	WriteData<5>((int*)0x751c6e, 0x90);	
	//WriteData<4>((int*)0x74e175, 0x90);

	//WriteCall((void*)0x6E5EDB, DoPulleyAction_r);


	if (isCustomAnim) {
		Miles_SpinInit();
		WriteJump(reinterpret_cast<void*>(0x7512ea), CheckVictoryPose);
	}
	
	voices_Init();
}