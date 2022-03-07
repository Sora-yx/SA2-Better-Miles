#pragma once

extern bool isTransform;
extern bool isTornadoOn;
extern bool isInMech;


enum TornadoE {
	tornadoInit,
	tornadoCall,
	tornadoMoveToPlayer1,
	tornadoMoveToPlayer2,
	tornadoTransition,
	tornadoTransition2,
	tornadoTransition3,
	tornadoPlayable,
	tornadoTransfoMech,
	tornadoExit
};

enum TornadoModeE {
	tornadoOff,
	tornadoPlaneMode,
	tornadoCycloneMode,
	tornadokartMode
};


void CallMech(ObjectMaster* obj);
void Load_TornadoTransfo_ModelsTextures();
void SoundEffect_Tornado(ObjectMaster* obj);

