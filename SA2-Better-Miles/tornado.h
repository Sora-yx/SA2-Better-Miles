#pragma once

extern bool isTransform;
extern bool isTornadoOn;
extern bool isInMech;

void CallMech(ObjectMaster* obj);
void Load_TornadoTransfo_ModelsTextures();
void SoundEffect_Tornado(ObjectMaster* obj);

enum TornadoModeE {
	tornadoOff,
	tornadoPlaneMode,
	tornadoCycloneMode,
	tornadokartMode
};
