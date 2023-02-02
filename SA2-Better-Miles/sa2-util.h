#pragma once

DataPointer(double, MilesFlySpeedValue, 0x9065a8);
//control/physic functions
FunctionPointer(void, sub_45B610, (EntityData1* data, EntityData2* a3, CharObj2Base* co2), 0x45B610);
FunctionPointer(void, sub_474990, (EntityData1* data, EntityData2* a3, CharObj2Base* co2), 0x474990);
FunctionPointer(void, PlayerGetRotation, (EntityData1* data, EntityData2* a3, CharObj2Base* co2), 0x45FA70);


FunctionPointer(void, Tails_runsAction, (EntityData1* data1, EntityData2* a2, CharObj2Base* a3, TailsCharObj2* a4), 0x74DC60);
ObjectFunc(PrisonLaneDoor4, 0x606A10);
FunctionPointer(int, LoadShEffTex, (), 0x755DE0);

FunctionPointer(signed int, sub_429710, (), 0x429710); //matrix stuff
FunctionPointer(signed int, sub_429000, (), 0x429000); //matrix stuff

FunctionPointer(int, AnimateMilesTails, (EntityData1* data1, CharObj2Base* a2, TailsCharObj2* a3), 0x751090);

FunctionPointer(void, DoGrindThing, (EntityData1* data, EntityData2* data2, CharObj2Base* co2, TailsCharObj2* co2Miles), 0x725F30);
FunctionPointer(double, SomethingAboutHandGrind, (EntityData1* a1, EntityData2* a2, TailsCharObj2* a3), 0x7271D0);
FunctionPointer(signed int, SomethingAboutHandGrind2, (EntityData1* a1, EntityData2* a2, TailsCharObj2* a3), 0x46D6D0);
FunctionPointer(int, calcGrindRotationMaybe, (NJS_VECTOR* v, Rotation* rot), 0x4905A0);
FunctionPointer(int, sub_447580, (NJS_OBJECT* v), 0x447580);
FunctionPointer(void, SetNewRot, (int a1, int a2, int a3), 0x46C490);
DataPointer(float, FLOAT_01283704, 0x1283704);
DataArray(float, flt_25F02A0, 0x25F02A0, 5);

DataPointer(DWORD, dword_267053C, 0x267053C); //something checked for after image


VoidFunc(sub_47BB50, 0x47BB50);



DataPointer(__int16, ActiveLandTableColCount, 0x1DE9484);
DataPointer(int, DebugMode2_, 0x174AFF9);
DataPointer(char, byte_1738C69, 0x1738C69);
DataPointer(__int16, word_1738D58, 0x1738D58);
FunctionPointer(double, FloatCalcResult, (float a1, float a2, float a3), 0x447520);
FunctionPointer(ObjectMaster*, DrawSubtitles, (int a1, const char* message, int displayTime, int language), 0x6B6E20);

ObjectFunc(sub_75DF80, 0x75DF80);

VoidFunc(DeleteLevelStuff, 0x43D510);

FunctionPointer(DWORD*, DisplayMessage, (char* a1, int language, __int16 a3, __int16 a4), 0x6B7F40);
FunctionPointer(unsigned int, CCL_CalcColli, (ObjectMaster* a1, int a2), 0x485850);


static const void* const sub_45E300Ptr = (void*)0x45E300;
static inline int  PhysicsBoardStuff(CharObj2Base* a1, EntityData1* a2, EntityData2* a3, float a4)
{
	int result;
	__asm
	{
		push[a4]
		push[a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_45E300Ptr
		add esp, 8
		mov result, eax
	}
	return result;
}


static const void* const boardPtr = (void*)0x727540;
static inline void BoardSparklesMaybe(EntityData2* a1, EntityData1* a2, TailsCharObj2* a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call boardPtr
		add esp, 8
	}
}


static const void* const sub_45E9A0Ptr = (void*)0x45E9A0;
static inline float PhysicsBoardStuff2(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	float result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, a1
		call sub_45E9A0Ptr
		add esp, 8
		fstp result
	}
	return result;
}



static const void* const Sub4372E0Ptr = (void*)0x4372E0;
static inline char Play3DSound2(int id, NJS_VECTOR* pos, int a3, char a4, char a5)
{
	char result;
	__asm
	{
		push[a5]
		push[a4]
		push[a3]
		mov esi, [pos]
		mov edi, [id]
		call Sub4372E0Ptr
		add esp, 12
		mov result, al
	}
	return result;
}


static const void* const SetNextAnimPtr = (void*)0x474F80;
static inline int PlayerChangeRunningMotion(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		call SetNextAnimPtr
		add esp, 4
		mov result, ebx
	}
	return result;
}

static const void* const  sub_4745D0ptr = (void*)0x4745D0;
static inline int sub_4745D0(CharObj2Base* a1, EntityData1* a2, EntityData2* a3)
{
	int result;
	__asm
	{
		push[a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_4745D0ptr
		add esp, 4
		mov result, eax
	}
	return result;
}

static const void* const  sub_474630ptr = (void*)0x474630;
static inline void sub_474630(CharObj2Base* a1, EntityData2* a2, EntityData1* a3)
{
	__asm
	{
		mov ebx, [a3]
		mov ecx, [a2]
		mov eax, [a1]
		call sub_474630ptr
	}
}

static const void* const sub_45B2C0Ptr = (void*)0x45B2C0;
static inline int sub_45B2C0(CharObj2Base* a1, int a2, EntityData1* a3)
{
	int result;

	__asm
	{
		mov esi, [a3]
		mov ecx, [a2]
		mov edx, [a1]

		call sub_45B2C0Ptr
		mov result, edx
	}

	return result;
}



static const void* const CheckGrindPtr = (void*)0x726D00;
static inline signed int CheckTrick(TailsCharObj2* a1, CharObj2Base* a2, EntityData1* a3)
{
	signed int result;

	__asm
	{
		push[a3]
		mov edi, [a2]
		mov eax, [a1]

		call CheckGrindPtr
		add esp, 8 // a2
		mov result, eax
	}
	return result;
}


static const void* const PConvertVPtr = (void*)0x468DF0;
static inline void PConvertVector_G2P(EntityData1* a1, NJS_VECTOR* a2)
{
	__asm
	{
		mov esi, [a2]
		mov edi, [a1]
		call PConvertVPtr
	}
}

static const void* const sub721480ptr = (void*)0x721480;
static inline HomingAttackTarget* sub_721480(CharObj2Base* a1, EntityData1* a2, float a3)
{
	HomingAttackTarget* result;
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]
		call sub721480ptr
		add esp, 8
		mov result, eax
	}
	return result;
}

static const void* const GetBufferedPositionAndRotPtr = (void*)0x46DBF0;
static inline signed int GetBufferedPositionAndRot(int a1, int a2, NJS_VECTOR* a3, char a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov esi, [a3]
		mov edi, [a2]
		mov eax, [a1]
		call GetBufferedPositionAndRotPtr
		add esp, 4
		mov result, eax
	}
	return result;
}


static const void* const SlowDownThingPtr = (void*)0x45F840;
static inline float SlowDownThing(EntityData1* a1, EntityData2* a2, CharObj2Base* a3)
{
	float result;
	__asm
	{
		mov ebx, a3
		mov eax, a2
		mov ecx, a1
		call SlowDownThingPtr
		fstp result
	}
	return result;
}


static const void* const PlayerCheckFallGravityPtr = (void*)0x4751D0;
static inline int PlayerCheckFallGravityStuff(EntityData1* a1, int a2, EntityData2* a3, CharObj2Base* a4)
{
	int result;
	__asm
	{
		push[a4] // a4
		push[a3] // a3
		mov ecx, [a2] // a1
		mov eax, [a1]
		// Call your __cdecl function here:
		call PlayerCheckFallGravityPtr
		add esp, 12 // a1<eax> is also used for return value
		mov result, eax
	}
	return result;
}


static const void* const somethingAboutTrick3Ptr = (void*)0x474F80;
static inline int somethingAboutTrick3(CharObj2Base* a1, EntityData1* a2)
{
	int result;
	__asm
	{
		push[a2]
		mov ebx, [a1]
		// Call your __cdecl function here:
		call somethingAboutTrick3Ptr
		add esp, 4
		mov result, eax
	}
	return result;
}


static const void* const sub_4EC330Ptr = (void*)0x4EC330;
static inline void sub_4EC330(int a1, int a2, int a3)
{
	__asm
	{
		mov ecx, [a3] // a3
		mov ebx, [a2] // a2
		mov edx, [a1] // a1
		// Call your __cdecl function here:
		call sub_4EC330Ptr
	}
}

//Math stuff that allow character to move on the rail
static const void* const sub_46D040Ptr = (void*)0x46D040;
static inline void sub_46D040(EntityData1* a1, CharObj2Base* a2, EntityData2* a3)
{
	__asm
	{
		push[a3]
		mov ebx, [a2]
		mov eax, [a1]
		call sub_46D040Ptr
		add esp, 4 // a3
	}
}

static const void* const sub_46D140Ptr = (void*)0x46D140;
static inline void getRailAccel(CharObj2Base* a1, EntityData1* a2, EntityData2* a3)
{
	__asm
	{
		push[a3]
		push[a2]
		mov eax, [a1]

		// Call your __cdecl function here:
		call sub_46D140Ptr
		add esp, 8 // a2
	}
}

static const void* const sub_754EC0Ptr = (void*)0x754EC0;
static inline void sub_754EC0(int playernum)
{
	__asm {
		mov ebx, [playernum]
		call sub_754EC0Ptr
	}
}

static const void* const sub_7274F0Ptr = (void*)0x7274F0;
static inline void sub_7274F0(EntityData1* a1)
{
	
	__asm
	{
		mov eax, [a1] 
		call sub_7274F0Ptr
	}
}


static const void* const njScaleExPtr = (void*)0x429740;
static inline void njScaleEx(NJS_VECTOR* a1)
{
	__asm
	{
		mov eax, [a1]
		call njScaleExPtr
	}
}



static const void* const sub_46C6D0PTR = (void*)0x46C6D0;
static inline void sub_46C6D0(int a1, float a2, float a3, float a4)
{
	__asm
	{
		push[a4]
		push[a3]
		push[a2]
		mov eax, [a1]
		call  sub_46C6D0PTR
		add esp, 12
	}
}

//void __usercall PoseEffectMan_Load(int a1@<eax>, int arg0)
static const void* const PoseEffectMan_r = (void*)0x477490;
static inline void PoseEffectMan_Load_(int a1, int a2)
{
	__asm
	{
		push[a2]
		mov eax, [a1]
		call PoseEffectMan_r
		add esp, 4
	}
}


#pragma pack(push, 1)
struct cartStruct
{
	NJS_POINT3 Velocity;
	Float idk;
	Float idk2;
	NJS_VECTOR Position;
	Rotation Forward;
	Float DistanceWall;
	int KartAction;
	Float idk3;
	Float SpeedY;
	Float SpeedX;
	Float Accel;
	Float idk5;
};
#pragma pack(pop)

struct _camcontwk
{
	char cammode;
	char camsmode;
	char bBlank;
	char btimer;
	unsigned __int16 wtimer;
	__int16 ssFlag;
	float tgtdist;
	NJS_VECTOR pos;
	NJS_VECTOR targetpos;
	Rotation angle;
	NJS_VECTOR oldcampos;
	int angx_spd;
	int angy_spd;
	int angz_spd;
	NJS_VECTOR speed;
	NJS_VECTOR acceleration;
};


static inline void Miles_InitLightDash(EntityData1* data, CharObj2Base* co2, EntityData2* data2, TailsCharObj2* a5)
{
	__asm
	{
		push[a5]
		push[data2]
		mov eax, [co2]
		mov ecx, [data]
		call lightdashptr
		add esp, 8
	}
}

VoidFunc(sub_48BDF0, 0x48BDF0);

static inline signed int Tails_CheckActionWindow_(EntityData1* a1, EntityData2* a2, CharObj2Base* a3, TailsCharObj2* a4)
{
	signed int result;
	__asm
	{
		push[a4]
		mov ecx, [a3]
		mov edx, [a2]
		mov eax, [a1]
		call Tails_CheckActionWindowPtr
		add esp, 4
		mov result, eax
	}
	return result;
}

//int __usercall Miles_CheckNextActions@<eax>(EntityData2 *a2@<ecx>, TailsCharObj2 *ebx0@<ebx>, CharObj2Base *a3@<edi>, EntityData1 *a4@<esi>)
static const void* const MilesCheckInputPtr = (void*)0x751CB0;
static inline signed int MilesCheckInput(EntityData2* a1, TailsCharObj2* a2, CharObj2Base* a3, EntityData1* a4)
{
	signed int result;

	__asm
	{
		mov esi, [a4]
		mov edi, [a3]
		mov ebx, [a2]
		mov ecx, [a1]
		call MilesCheckInputPtr
		mov result, eax
	}
	return result;
}
