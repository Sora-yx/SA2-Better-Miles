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

Buttons RollBtn = Buttons_B;
Buttons BounceBtn = Buttons_B;
Buttons SpinBtn = Buttons_X;
Buttons LightDashBtn = Buttons_Y;

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

	RollBtn = (Buttons)config->getInt("pad", "RollBtn", RollBtn);
	BounceBtn = (Buttons)config->getInt("pad", "BounceBtn", BounceBtn);
	SpinBtn = (Buttons)config->getInt("pad", "SpinBtn", SpinBtn);
	LightDashBtn = (Buttons)config->getInt("pad", "LightDashBtn", LightDashBtn);

	flySoundEffect = config->getBool("Audio", "flySoundEffect", true);
	jumpVoice = config->getBool("Audio", "jumpVoice", false);
	delete config;

	if (isSA1Char(Characters_Tails))
		isJumpBall = true;

	return;
}