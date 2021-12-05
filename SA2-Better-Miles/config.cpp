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


void ReadConfig(const char* path) {

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	isCustomPhysics = config->getBool("General", "isCustomPhysics", true);
	isCustomAnim = config->getBool("General", "isCustomAnim", true);
	isMechRemoved = config->getBool("General", "isMechRemoved", true);
	isMilesAdventure = config->getBool("General", "isMilesAdventure", false);

	isInfiniteFly = config->getBool("Abilities", "isInfiniteFly", false);
	isLightDash = config->getBool("Abilities", "isLightDash", true);
	isBounce = config->getBool("Abilities", "isBounce", true);

	flySoundEffect = config->getBool("Audio", "flySoundEffect", true);
	jumpVoice = config->getBool("Audio", "jumpVoice", false);
	delete config;

	return;
}