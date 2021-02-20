#include "stdafx.h"

StartPosition MilesStartArray[] = {
	{ LevelIDs_BasicTest, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_GreenForest, 0x4000, 0x4000, 0x4000, { 1.61f, 40, -416 }, { 15, 40, -416 }, { -15, 40, -416 } },
	{ LevelIDs_WhiteJungle, 0x4000, 0x4000, 0x4000, { 0, -85, -45 }, { 15, -80, -45 }, { -15, -80, -45 } },
	{ LevelIDs_PumpkinHill, 0xD000, 0xD000, 0xD000, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -9.5f, 800, -526.1438f }, { -9.5f, 800, -526.1438f }, { 8.7f, 800, -526.1438f } },
	{ LevelIDs_AquaticMine, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_SecurityHall, 0xA000, 0xA000, 0xE000, { 405, -830, 410 }, { 405, -830, 410 }, { -405, -830, 410 } },
	{ LevelIDs_PrisonLane, 0x8000, 0x8000, 0x8000, { 115, 10, 4 }, { 115, 10, 4 }, { 115, 10, 4 } },
	{ LevelIDs_MetalHarbor, 0xC000, 0xC000, 0xC000, { 0, 500, 40 }, { 10, 500, 45 }, { -10, 500, 45 } },
	{ LevelIDs_IronGate, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_WeaponsBed, 0xC000, 0xC000, 0xC000, { 0 }, { 10, 0, 0 }, { -10, 0, 0 } },
	{ LevelIDs_CityEscape, 0x4000, 0x4000, 0x4000, { 0, 300, 340 }, { 10, 300, 340 }, { -10, 300, 340 } },
	{ LevelIDs_RadicalHighway, 0xC000, 0xC000, 0xC000, { 103, 182, -39 }, { 103, 182, -39 }, { -103, 182, -39 } },
	{ LevelIDs_WeaponsBed2P, 0xC000, 0xC000, 0x4000, { 50, -170, 50 }, { 20, -170, 95 }, { 20, -170, -95 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 65.2f, -400 }, { 180, 65.2f, -400 } },
	{ LevelIDs_MissionStreet, 0xC000, 0xC000, 0xC000, { 0, 200, 0 }, { 0, 200, 0 }, { 0, 200, 0 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 65, -400 }, { 200, 65, -400 }, { 200, 65, -400 } },
	{ LevelIDs_SonicVsShadow1, 0, 0, 0, { -60, 64, 0 }, { -60, 64, 0 }, { -60, 64, 0 } },
	{ LevelIDs_TailsVsEggman1, 0xB200, 0xB200, 0xB200, { 50, -170, 50 }, { 50, -170, 50 }, { 50, -170, 50 } },
	{ LevelIDs_SandOcean, 0xC000, 0xC000, 0xC000, { 0, 80, 0 }, { 0, 80, 0 }, { 0, 80, 0 } },
	{ LevelIDs_CrazyGadget, 0xC000, 0xC000, 0xC000, { 0, 180, 340 }, { 20, 180, 340 }, { -20, 180, 340 } },
	{ LevelIDs_HiddenBase, 0xC000, 0xC000, 0xC000, { 0, 140, 0 }, { 0, 140, 0 }, { 0, 140, 0 } },
	{ LevelIDs_EternalEngine, 0xC000, 0xC000, 0xC000, { 0, 370, 0 }, { 0, 370, 0 }, { 0, 370, 0 } },
	{ LevelIDs_DeathChamber, 0xA000, 0x8000, 0xC000, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },
	{ LevelIDs_EggQuarters, 0xA000, 0xC000, 0xC000, { 940, -30, 940 }, { 20, 110, 40 }, { -20, 110, 40 } },
	{ LevelIDs_LostColony, 0xC000, 0xC000, 0xC000, { 0, -175, 29 }, { 0, -175, 29 }, { 0, -175, 29 } },
	{ LevelIDs_PyramidCave, 0xC000, 0xC000, 0xC000, { 0, 300, 0 }, { 0, 300, 0 }, { 0, 300, 0 } },
	{ LevelIDs_TailsVsEggman2, 0xB200, 0xB200, 0xB200, { 50, -50, 80 }, { 50, -50, 80 }, { 50, -50, 80 } },
	{ LevelIDs_FinalRush, 0, 0, 0, { -100, 0, 0 }, { -100, 0, -25 }, { -100, 0, 25 } },
	{ LevelIDs_GreenHill, 0xC000, 0xC000, 0xC000, { 0, 40, 0 }, { 15, 40, 0 }, { -15, 40, 0 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -450, -1025 }, { 25, -450, -1025 }, { -25, -450, -1025 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { -20, 0, 0 }, { -20, 0, 0 }, { -20, 0, 0 } },
	{ LevelIDs_CannonsCoreS, 0xC000, 0xC000, 0xC000, { 0, 45, 0 }, { 0, 45, 0 }, { 0, 45, 0 } },
	{ LevelIDs_CannonsCoreE, 0xC000, 0xC000, 0xC000, { 0, 20.1f, -200 }, { 0, 20.1f, -200 }, { 0, 20.1f, -200 } },
	{ LevelIDs_CannonsCoreT, 0xC000, 0xC000, 0xC000, { 0, 670, 0 }, { 0, 670, 0 }, { 0, 670, 0 } },
	{ LevelIDs_CannonsCoreR, 0xC000, 0xC000, 0xC000, { 0, 480, 150 }, { 0, 480, 150 }, { 0, 480, 150 } },
	{ LevelIDs_CannonsCoreK, 0x8000, 0x8000, 0x8000, { 0, 580, 60 }, { 0, 580, 60 }, { 0, 580, 60 } },

	{ LevelIDs_MissionStreet2P, 0, 0, 0x8000, { -520, 0, 0 }, { -520, 0, 0 }, { 0 } },
	{ LevelIDs_FinalChase, 0, 0x4000, 0x4000, { -223, -100, 63 }, { 3206, -4000, 2455 }, { 3176, -4000, 2455 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0x4000, 0x4000, { 200, 100, -400 }, { 220, 66, -345 }, { 180, 66, -345 } },
	{ LevelIDs_SonicVsShadow2, 0, 0, 0, { 0, 0, -15 }, { 0, 0, -15 }, { 0, 0, -15 } },
	{ LevelIDs_CosmicWall, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_MadSpace, 0x7000, 0xC000, 0xC000, { 0, 660, 0 }, { 30, 630, 17 }, { 0, 630, -35 } },
	{ LevelIDs_SandOcean2P, 0, 0, 0x8000, { -60, 35, 0 }, { -60, 35, 0 }, { 60, 35, 0 } },

	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 220, 210, 1350 }, { 225, 480, 1325 }, { 185, 480, 1325 } },
	{ LevelIDs_PyramidRace, 0, 0xC000, 0xC000, { 0 }, { -35, 10, -20 }, { 35, 10, -20 } },
	{ LevelIDs_HiddenBase2P, 0, 0, 0x8000, { 60, 0, 10 }, { -60, 0, 10 }, { 60, 0, 10 } },
	{ LevelIDs_PoolQuest, 0x4000, 0x4000, 0x4000, { 0, 155, -233 }, { 10, 155, -233 }, { -10, 155, -233 } },
	{ LevelIDs_PlanetQuest, 0, 0x4000, 0x4000, { 0, 660, 0 }, { -470, 1500, -630 }, { -430, 1500, -630 } },

	{ LevelIDs_DeckRace, 0xC000, 0xC000, 0xC000, { 0 }, { -15, -170, 1480 }, { 15, -170, 1480 } },
	{ LevelIDs_DowntownRace, 0x4000, 0x4000, 0x4000, { -2215, 4320, -4670 }, { -2235, 4320, -4670 }, { -2195, 4320, -4670 } },

	{ LevelIDs_CosmicWall2P, 0, 0, 0x8000, { -80, 0, 0 }, { -80, 0, 0 }, { 80, 0, 5 } },
	{ LevelIDs_GrindRace, 0, 0, 0, { 10, -445, -900 }, { 10, -795, -900 }, { -10, -795, -900 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x8000, { -280, 150, 280 }, { -280, 150, 280 }, { 280, 150, -280 } },
	{ LevelIDs_EternalEngine2P, 0x4000, 0x4000, 0xC000, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_MetalHarbor2P, 0xC000, 0xC000, 0xC000, { 0, 500, 40 }, { -10, 500, 45 }, { 10, 500, 45 } },
	{ LevelIDs_IronGate2P, 0, 0, 0x8000, { 0 }, { -50, -10, -20 }, { 50, -10, -20 } },
	{ LevelIDs_DeathChamber2P, 0xA000, 0x8000, 0xC000, { 870, 70, 870 }, { 0, 240, 180 }, { 180, 240, 0 } },

	{ LevelIDs_KingBoomBoo, 0, 0, 0, { 276, -40, 190 }, { 276, -40, 190 }, { 276, -40, 190 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 210 }, { 0, 200, 210 }, { 0, 200, 210 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, 1000 }, { 0, 0, 1000 }, { 0, 0, 1000 } },
	{ LevelIDs_EggGolemE, 0, 0, 0, { 0, 200, 210 }, { 0, 200, 210 }, { 0, 200, 210 } },
	{ LevelIDs_Invalid }
};

LevelEndPosition CharacterEndArrayM2M3[] = {
	{ LevelIDs_GreenForest, 0x8000, 0x8000, 0, { 5858, -1812, 7541 }, { 6890, -1610, 7542 } },
	{ LevelIDs_WhiteJungle, 0xC000, 0xB000, 0, { 5040, -2220, -1550 }, { 13280, -3157, -7370 } },
	{ LevelIDs_PumpkinHill, 0x8000, 0xC000, 0, { 530, -986, -770 }, { -13, 34.8f, 1275 } },
	{ LevelIDs_SkyRail, 0x8000, 0xA000, 0, { -2411, -1792, 4260 }, { -3457, -1047, 3001 } },
	{ LevelIDs_AquaticMine, 0, 0, 0, { 0, 130, -365 }, { -600, 211, 443 } },
	{ LevelIDs_SecurityHall, 0, 0x4000, 0, { 100, -573, 490 }, { 0, 314.6f, 110 } },
	{ LevelIDs_PrisonLane, 0x8000, 0x8000, 0, { -350, 117, 410 }, { -3129, 790, -242 } },
	{ LevelIDs_MetalHarbor, 0, 0x4000, 0, { 2158, -160, -5294 }, { 1707, -170, -6583 } },
	{ LevelIDs_IronGate, 0x8000, 0xC000, 0, { 1490, -270, -1025 }, { 3184, -233, -702 } },
	{ LevelIDs_WeaponsBed, 0x4000, 0xFA00, 0, { -4, -160, -40 }, { 1500, -220, -6008 } },
	{ LevelIDs_CityEscape, 0xC000, 0x4000, 0, { -1570, -6060, 8860 }, { 7700, -13145, 5570 } },
	{ LevelIDs_RadicalHighway, 0xC000, 0x8000, 0, { -40, -400, -970 }, { -6330, -4500, -8830 } },
	{ LevelIDs_WildCanyon, 0xC000, 0xC000, 0, { 705, 1010, -14 }, { 1700, 0, 121 } },
	{ LevelIDs_MissionStreet, 0x8000, 0, 0, { 2200, 800, -3500 }, { 4065, 758, -4170 } },
	{ LevelIDs_DryLagoon, 0x8000, 0x7000, 0, { 191, 211, 1317 }, { 1728, 0, -382 } },
	{ LevelIDs_SandOcean, 0x4000, 0x4A00, 0, { 0, 80, 0 }, { 659, 120, -4660 } },
	{ LevelIDs_CrazyGadget, 0xC000, 0x8000, 0, { -9710, -1045, -4005 }, { -8725, -537, -2905 } },
	{ LevelIDs_HiddenBase, 0, 0x4000, 0, { -2295, 110, -2845 }, { -3525, 920, -4960 } },
	{ LevelIDs_EternalEngine, 0x4000, 0x4000, 0, { -2055, 936, -5825 }, { -652, 788, -4426 } },
	{ LevelIDs_DeathChamber, 0, 0xE000, 0, { 100, 100, 180 }, { -805, -35, -805 } },
	{ LevelIDs_EggQuarters, 0x8000, 0x8000, 0, { 100, 70, 1255 }, { -655, -20, 2680 } },
	{ LevelIDs_LostColony, 0x8000, 0, 0, { 595, -518, -2350 }, { 2225, -308, -2400 } },
	{ LevelIDs_PyramidCave, 0x4000, 0, 0, { -685, -4190, -19525 }, { -2170, -3970, -21870 } },
	{ LevelIDs_FinalRush, 0, 0xC000, 0, { 5776, -15687, 20080 }, { 4207, -16632, 24462 } },
	{ LevelIDs_MeteorHerd, 0, 0x5200, 0, { 10, 170, 140 }, { -438, 2752, -432 } },
	{ LevelIDs_CannonsCoreS, 0x4000, 0x4000, 0, { 0, -480, -1550 }, { -510, -655, -4700 } },
	{ LevelIDs_CannonsCoreE, 0, 0xFFFF, 0, { 80, -30, -1570 }, { 0, 20, -200 } },
	{ LevelIDs_CannonsCoreT, 0, 0xFFFF, 0, { -1050, 638, -1540 }, { 0, 670, 0 } },
	{ LevelIDs_CannonsCoreR, 0x4000, 0xFFFF, 0, { 80, 135, 80 }, { 0, 480, 150 } },
	{ LevelIDs_CannonsCoreK, 0xC000, 0xFFFF, 0, { 0, 660, -160 }, { 0, 580, 60 } },
	{ LevelIDs_FinalChase, 0xC000, 0xE000, 0, { 3408, -6592, 16865 }, { -695, -6959.5f, 10275 } },
	{ LevelIDs_CosmicWall, 0x4000, 0xA000, 0, { 6673, 4000, 11677 }, { 2753, 2583, -1045 } },
	{ LevelIDs_MadSpace, 0xEC00, 0, 0, { 272.5f, 2358, -334.5f }, { -154, 3350, 481 } },
	{ LevelIDs_Invalid }
};

StartPosition CharacterEndArray[] = {
	{ LevelIDs_GreenForest, 0x8000u, 0x8000u, 0x8000u, { 10935, -1854, 11056 }, { 10935, -1854, 11076 }, { 10935, -1854, 11066 } },
	{ LevelIDs_WhiteJungle, 0xC000u, 0xC000u, 0xC000u, { 13166, -3599, -5518 }, { 9135, -3154, -4930 }, { 9135, -3154, -4930 } },
	{ LevelIDs_PumpkinHill, 0xD000u, 0xD000u, 0xD000u, { 199, -1361, -1035 }, { 188.63f, -1361, -1045 }, { 208.3f, -1361, -1021.5f } },
	{ LevelIDs_SkyRail, 0x4000, 0x4000, 0x4000, { -1343.7f, -4928, 10098 }, { -1333.7f, -4928, 10098 }, { -1353.7f, -4928, 10098 } },
	{ LevelIDs_AquaticMine, 0x4000, 0, 0, { 0, 130, -340 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_SecurityHall, 0xA000u, 0x6000, 0xA000u, { 405, -933, 410 }, { 217, -933, 410 }, { 217, -933, 410 } },
	{ LevelIDs_PrisonLane, 0xC000u, 0xC000u, 0xC000u, { -4440, 940, -1178 }, { -4440, 940, -1178 }, { -4440, 940, -1178 } },
	{ LevelIDs_MetalHarbor, 0x6000, 0, 0, { 8777, -170, -10240 }, { 8854, -170, -10241 }, { 8854, -170, -10281 } },
	{ LevelIDs_IronGate, 0, 0, 0, { 6150, -1521, -1230 }, { 6150, -1521, -1230 }, { 6150, -1521, -1230 } },
	{ LevelIDs_WeaponsBed, 0, 0, 0, { 4251, -220, -10138 }, { 4231, -220, -10138 }, { 4281, -220, -10138 } },
	{ LevelIDs_CityEscape, 0x4000, 0x8000u, 0x8000u, { 3955, -22175, 16130 }, { 6450, -15915, 9070 }, { 6450, -15915, 9070 } },
	{ LevelIDs_RadicalHighway, 0xC000u, 0xC000u, 0xC000u, { -9970, -6999, -18430 }, { -9970, -6999, -18350 }, { -9970, -6999, -18350 } },
	{ LevelIDs_WeaponsBed2P, 0x4000, 0x4000, 0x4000, { 140, -170, 20 }, { 140, -170, 20 }, { 140, -170, 20 } },
	{ LevelIDs_WildCanyon, 0x4000, 0x4000, 0x4000, { 200, 856, -140 }, { 220, 856, -140 }, { 180, 856, -140 } },
	{ LevelIDs_MissionStreet, 0xC000u, 0xC000u, 0xC000u, { 7170, 598, -6913 }, { 7170, 598, -6913 }, { 7170, 598, -6913 } },
	{ LevelIDs_DryLagoon, 0x4000, 0x4000, 0x4000, { 200, 15, -140 }, { 200, 15, -140 }, { 200, 15, -140 } },
	{ LevelIDs_SonicVsShadow1, 0x6C00, 0x6C00, 0x6C00, { 10, -42, 0 }, { 10, -42, 0 }, { 10, -42, 0 } },
	{ LevelIDs_TailsVsEggman1, 0x4000, 0x4000, 0x4000, { 140, -170, 20 }, { 140, -170, 20 }, { 140, -170, 20 } },
	{ LevelIDs_SandOcean, 0x8000u, 0x8000u, 0x8000u, { 2895, 155, -7185 }, { 2895, 155, -7185 }, { 2895, 155, -7185 } },
	{ LevelIDs_CrazyGadget, 0xC000u, 0xC000u, 0xC000u, { -8470, -1097, -2904 }, { -8470, -1097, -2904 }, { -8470, -1097, -2904 } },
	{ LevelIDs_HiddenBase, 0x4000, 0x4000, 0x4000, { -3035, 1280, -5400 }, { -3035, 1280, -5400 }, { -3035, 1280, -5400 } },
	{ LevelIDs_EternalEngine, 0xC000u, 0xC000u, 0xC000u, { 207, -1826, -9150 }, { 207, -1826, -9150 }, { 207, -1826, -9150 } },
	{ LevelIDs_DeathChamber, 0x2000, 0x2000, 0x2000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_EggQuarters, 0x2000, 0xA000u, 0xA000u, { 980, -30, 980 }, { -820, 20, 820 }, { -820, 20, 820 } },
	{ LevelIDs_LostColony, 0, 0, 0, { 4710, 1552, -2400 }, { 4710, 1552, -2400 }, { 4710, 1552, -2400 } },
	{ LevelIDs_PyramidCave, 0x4000, 0x4000, 0x4000, { 940, -4060, -22190 }, { 940, -4060, -22190 }, { 940, -4060, -22190 } },
	{ LevelIDs_TailsVsEggman2, 0x4000, 0x4000, 0x4000, { 0, -50, -181.5f }, { 0, -50, -181.5f }, { 0, -50, -181.5f } },
	{ LevelIDs_FinalRush, 0, 0x4000, 0x4000, { 2530, -26495.5f, 7465 }, { 2531, -20965, 11350 }, { 2531, -20965, 11350 } },
	{ LevelIDs_GreenHill, 0xC000u, 0xC000u, 0xC000u, { -1970, -1390, -6940 }, { -1970, -1390, -6940 }, { -1970, -1390, -6910 } },
	{ LevelIDs_MeteorHerd, 0x4000, 0x4000, 0x4000, { 0, -500, -1025 }, { 25, -500, -1025 }, { -25, -500, -1025 } },
	{ LevelIDs_KnucklesVsRouge, 0, 0, 0, { 0, -340, 10 }, { 0, -340, 10 }, { 0, -340, 10 } },
	{ LevelIDs_CannonsCoreS, 0x1000, 0x1000, 0x1000, { -1600, -5755, -9565 }, { -308, 0, 0 }, { -308, 0, 0 } },
	{ LevelIDs_CannonsCoreE, 0xC000u, 0xC000u, 0xC000u, { 570, -2630, -3450 }, { 570, -2630, -3450 }, { 570, -2630, -3450 } },
	{ LevelIDs_CannonsCoreT, 0xC000, 0xC000, 0xC000, { 0, 670, 0 }, { 0, 670, 0 }, { 0, 670, 0 } },
	{ LevelIDs_CannonsCoreR, 0x8000u, 0x8000u, 0x8000u, { 120, 20, 0 }, { 120, 20, 0 }, { 120, 20, 0 } },
	{ LevelIDs_CannonsCoreK, 0, 0, 0, { -435, -175, -1735 }, { -435, -175, 1735 }, { -435, -175, 1735 } },
	{ LevelIDs_MissionStreet2P, 0xC000u, 0xC000u, 0xC000u, { 0, 0, -25 }, { 0, 0, -25 }, { 0, 0, -25 } },
	{ LevelIDs_FinalChase, 0, 0xC000u, 0xC000u, { 122, -9960, 7627 }, { 3440, -6812, 17730 }, { 3440, -6812, 17730 } },
	{ LevelIDs_WildCanyon2P, 0x4000, 0xF000u, 0xF000u, { 200, 856, -140 }, { -359, 927, -44 }, { -359, 927, -44 } },
	{ LevelIDs_SonicVsShadow2, 0x4000, 0x4000, 0x4000, { -292, 0, 0 }, { -292, 0, 0 }, { -292, 0, 0 } },
	{ LevelIDs_CosmicWall, 0x8000u, 0x8000u, 0x8000u, { 3550, -1600, 29690 }, { 3550, -1600, 29690 }, { 3550, -1600, 29690 } },
	{ LevelIDs_MadSpace, 0xF000u, 0xF000u, 0xF000u, { 0, 620, 0 }, { 0, 620, 5 }, { 0, 620, 5 } },
	{ LevelIDs_SandOcean2P, 0x4000, 0x4000, 0x4000, { 17, 30, -150 }, { 17, 30, -150 }, { 17, 30, -150 } },
	{ LevelIDs_DryLagoon2P, 0x4000, 0x4000, 0x4000, { 200, 210, 1350 }, { 200, 210, 1350 }, { 200, 210, 1350 } },
	{ LevelIDs_PyramidRace, 0, 0, 0, { 0 }, { 0, 0, -2020 }, { 0, 0, -2020 } },
	{ LevelIDs_HiddenBase2P, 0, 0x4000, 0x4000, { 0, 0, 30 }, { -20, 0, 25 }, { -20, 0, 25 } },
	{ LevelIDs_PoolQuest, 0, 0, 0, { 0, 130, -200 }, { 10, 130, -200 }, { -10, 130, -200 } },
	{ LevelIDs_PlanetQuest, 0, 0, 0, { 0, 620, 0 }, { -432, 1640.5f, -560 }, { -432, 1640.5f, -560 } },
	{ LevelIDs_DeckRace, 0xC000u, 0xC000u, 0xC000u, { 0 }, { 0, -170, -475 }, { 0, -170, -475 } },
	{ LevelIDs_DowntownRace, 0xC000u, 0xC000u, 0xC000u, { -1540, -6060, 8800 }, { -1540, -6060, 8800 }, { -1540, -6060, 8770 } },
	{ LevelIDs_GrindRace, 0x8000u, 0x8000u, 0x8000u, { 13990, -35280, 10050 }, { 13990, -35280, 10050 }, { 13990, -35280, 10050 } },
	{ LevelIDs_LostColony2P, 0, 0, 0x2000, { -150, 0, 0 }, { -150, 0, 0 }, { -280, 0, -170 } },
	{ LevelIDs_EternalEngine2P, 0x6000, 0x6000, 0x6000, { 0, -50, -120 }, { 0, -50, -120 }, { 0, -50, 120 } },
	{ LevelIDs_MetalHarbor2P, 0, 0x8000u, 0x8000u, { 8854, -31, -10370 }, { 4913, -31, -10370 }, { 4913, -31, -10370 } },
	{ LevelIDs_IronGate2P, 0, 0xC000u, 0xC000u, { 0 }, { -30, -10, -20 }, { -30, -10, -20 } },
	{ LevelIDs_DeathChamber2P, 0x2000, 0x2000, 0x2000, { 830, 20, 830 }, { 830, 20, 830 }, { 830, 20, 830 } },
	{ LevelIDs_BigFoot, 0, 0, 0, { 0, -1, 0 }, { 0, -1, 0 }, { 0, -1, 0 } },
	{ LevelIDs_HotShot, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_FlyingDog, 0, 0, 0, { 0 }, { 0 }, { 0 } },
	{ LevelIDs_KingBoomBoo, 0x1800, 0x1800, 0x1800, { 374, -40, -120 }, { 374, -40, -120 }, { 374, -40, -120 } },
	{ LevelIDs_EggGolemS, 0, 0, 0, { 0, 200, 220 }, { 0, 200, 220 }, { 0, 200, 220 } },
	{ LevelIDs_Biolizard, 0, 0, 0, { -265, 10, 0 }, { -265, 10, 0 }, { -265, 10, 0 } },
	{ LevelIDs_FinalHazard, 0, 0, 0, { 0, 0, -1000 }, { 0, 0, -1000 }, { 0, 0, -1000 } },
	{ LevelIDs_EggGolemE, 0, 0, 0, { 0, 200, 220 }, { 0, 200, 220 }, { 0, 200, 220 } },
};


static inline void SetEndPosition() {

	if (CurrentLevel == LevelIDs_Route101280)
		return;

	if (MainCharObj2[0]->CharID == Characters_Tails) {

		int num = -1;

		if (CurrentLevel == LevelIDs_FinalHazard) {
			num = TailsRankVoices[4];
			MainCharObj2[0]->CharID = Characters_SuperSonic;
			PlayVoice(2, num); //"I did it Sonic" 
		}
		else {
			num = CurrentLevel == LevelIDs_TailsVsEggman1 ? 1715 : 1703;
			MainCharObj2[0]->CharID = Characters_Rouge; //Trick the game to make it thinks we are playing rouge, so we can get good camera and good ending position.
			PlayVoice(2, num); //"I did it" 
		}
	}

	return;
}


static void __declspec(naked) PlayWinnerVoiceProbablyASM()
{
	__asm
	{
		call SetEndPosition
		push esi // pnum

		// Call your __cdecl function here:
		call PlayWinnerVoiceProbablyPtr

		pop esi // pnum
		retn
	}
}


void Init_StartEndPos() {

	if (isRando() || isCharaSelect())
		return;


	WriteData((StartPosition**)0x43d955, MilesStartArray);
	WriteData((StartPosition**)0x43df89, CharacterEndArray); //Change Rouge End Array with a more complete one (used to trick the game)		
	WriteData((LevelEndPosition**)0x43ddfb, CharacterEndArrayM2M3); //Same with M2 and M3

	//Hack the victory function to fix Character and Camera position
	WriteCall((void*)0x44f864, PlayWinnerVoiceProbablyASM);
	WriteCall((void*)0x450816, PlayWinnerVoiceProbablyASM);
	WriteCall((void*)0x451017, PlayWinnerVoiceProbablyASM);
	WriteCall((void*)0x4510af, PlayWinnerVoiceProbablyASM);
}

