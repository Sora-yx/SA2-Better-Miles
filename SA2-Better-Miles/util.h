#pragma once

void PlayerMoveStuff(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);

bool isMilesAttacking();
bool isMilesAttackingBox();

void init_RankScore();
void CheckAndSetHackObject(CharObj2Base* co2);
void BoardSoundEffect(CharObj2Base* co2, EntityData1* data);

bool isRando();
bool isCharaSelect();
bool isSA1Char(uint8_t charID);

signed int Tails_CheckActionWindowR(EntityData1* a1, EntityData2* a2, CharObj2Base* a3, TailsCharObj2* a4);

int IsPlayerInsideSphere(NJS_VECTOR* position, float a2);
void DoNextAction_r(int playerNum, char action, int unknown);
int DiffAngle(int ang0, int ang1);

bool isSuperForm(char pID);
void Load_MilesNewAnim();
void Miles_LoadJmpBall(TailsCharObj2* mco2);
void LoadTornado_ModelAnim();

ModelInfo* LoadMDL(const char* name, ModelFormat format);
AnimationFile* LoadAnim(const char* name);
void FreeMDL(ModelInfo* pointer);
void FreeAnim(AnimationFile* pointer);
void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
bool isInTornado(char pNum);
void Tornado_Main(ObjectMaster* obj);
void Cart_CheckInput(CharObj2Base* co2, EntityData1* data1);
void SetCameraFacePlayer(char pNum, EntityData1* playerData, float zoom);
void Init_TailsMechHack();
void Delete_TornadoTransform();
void Delete_Tornado();
bool isBossLevel();
bool isMiles();
AnimationIndex* getCharAnim_r();
void SetCharacterAnim(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);