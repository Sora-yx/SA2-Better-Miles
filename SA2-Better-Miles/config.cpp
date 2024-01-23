#include "pch.h"

bool isCustomPhysics = true;
bool isCustomAnim = true;
bool isMechRemoved = false;
bool isMilesAdventure = false;

bool isInfiniteFly = false;
bool isLightDash = true;
bool isBounce = true;

bool flySoundEffect = true;
bool jumpVoice = false;

bool isJumpBall = true;
bool tornadoConfig = true;
bool tornadoMusic = true;
uint8_t sfxVol = 50;
uint8_t voiceVol = 50;

Buttons RollBtn = Buttons_B;
Buttons BounceBtn = Buttons_B;
Buttons SpinBtn = Buttons_X;
Buttons LightDashBtn = Buttons_Y;



static const Buttons ButtonsList[]
{
	Buttons_B,
	Buttons_X,
	Buttons_Y,
};


void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	isCustomPhysics = config->getBool("General", "isCustomPhysics", true);
	isCustomAnim = config->getBool("General", "isCustomAnim", true);
	isMechRemoved = config->getBool("General", "isMechRemoved", true);
	isMilesAdventure = config->getBool("General", "isMilesAdventure", false);
	isJumpBall = config->getBool("General", "isJumpBall", true);


	isInfiniteFly = config->getBool("Abilities", "isInfiniteFly", false);
	isLightDash = config->getBool("Abilities", "isLightDash", true);
	isBounce = config->getBool("Abilities", "isBounce", true);
	tornadoConfig = config->getBool("Abilities", "tornadoConfig", true);

	RollBtn = ButtonsList[config->getInt("pad", "RollBtn", 0)];
	BounceBtn = ButtonsList[config->getInt("pad", "BounceBtn", 0)];
	SpinBtn = ButtonsList[config->getInt("pad", "SpinBtn", 1)];
	LightDashBtn = ButtonsList[config->getInt("pad", "LightDashBtn", 2)];

	tornadoMusic = config->getBool("Audio", "tornadoMusic", true);
	flySoundEffect = config->getBool("Audio", "flySoundEffect", true);
	jumpVoice = config->getBool("Audio", "jumpVoice", false);
	sfxVol = config->getInt("Audio", "sfxVol", sfxVol);
	voiceVol = config->getInt("Audio", "voiceVol", voiceVol);
	delete config;

	if (isSA1Char(Characters_Tails))
		isJumpBall = true;

	return;
}