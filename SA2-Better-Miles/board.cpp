#include "pch.h"

void BoardSoundEffect(CharObj2Base* co2, EntityData1* data) {
	if (CurrentLevel == 10)
	{
		if (co2->Speed.x > 0.2000000029802322)
		{
			Play3DSound_EntityAndPos(data, 6, &data->Position, 2);
		}
	}
	else if (CurrentLevel == 13 || CurrentLevel == 52)
	{
		if (co2->Speed.x > 0.2000000029802322)
		{
			Play3DSound_EntityAndPos(data, 8, &data->Position, 2);
		}
	}
}


bool BoardStuff(EntityData2* data2, TailsCharObj2* co2Miles, EntityData1* data, CharObj2Base* co2) 
{

	if (MilesCheckInput(data2, co2Miles, co2, data))
	{
		return true;
	}

	if (CheckGravityFallThing(data, data2, co2))
	{
		data->Action = Action_BoardFall;
		co2->AnimInfo.Next = 129;
		return true;
	}

	if (Jump_Pressed[co2->PlayerNum])
	{
		data->Action = Action_BoardJump;
		co2->Speed.y = co2->PhysData.JumpSpeed + 1.5f; //stupid boost jump otherwise it goes back to ground even though you aren't, funny game :)
		co2->AnimInfo.Next = 127;

		if (co2->PhysData.RushSpeed > co2->Speed.x) //rushspeed
		{
			co2->Speed.x += co2->PhysData.JogSpeed; //jogspeed
		}

		auto v237 = co2->CurrentDyncolTask;
		if (!v237) //board trick someday
		{

		}

		data->Status &= 0xFFFDu;


		co2->field_12 = 0;
		data->Status &= ~Status_Ground;
		data->Status &= ~Status_OnObjectColli;
		return true;
	}

	return false;
}

void BoardJumpStuff(EntityData1* data, TailsCharObj2* co2Miles, CharObj2Base* co2, EntityData2* data2) {
	
	if (MilesCheckInput(data2, co2Miles, co2, data))
	{
		return;
	}

	if ((data->Status & 3) != 0)
	{

		data->Action = Action_Board;
		co2->AnimInfo.Next = 121;
		co2->AnimInfo.nframe = 0.0;
		if (co2->Speed.x <= 0.30000001)
		{
			co2->Speed.x = 1.0f;
		}
		;
		data->Rotation.x = data2->Forward.x;
		data->Rotation.z = data2->Forward.z;
		if (CurrentLevel == 13 || CurrentLevel == 52)
		{
			Play3DSound2(0, &data->Position, 0, 0, -10);
		}
		VibeThing(0, 15, co2->PlayerNum, 6);
	}
	else if (co2->Speed.y <= 0.0f && co2->AnimInfo.Current == 127)
	{
		co2->AnimInfo.Next = 128;
	}

	return;
}