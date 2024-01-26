#pragma once

void PlayerMoveStuff(EntityData1* a1, EntityData2* a2, CharObj2Base* a3);

bool isMilesAttacking();
bool isMilesAttackingBox(char pnum);

void init_RankScore();
void CheckAndSetHackObject(CharObj2Base* co2);
void BoardSoundEffect(CharObj2Base* co2, EntityData1* data);

bool isRando();
bool isCharaSelect();
bool isSA1Char(uint8_t charID);

void DoNextAction_r(int playerNum, char action, int unknown);
int DiffAngle(int ang0, int ang1);

bool isSuperForm(char pID);
void Load_MilesNewAnim();
void LoadTornado_ModelAnim();

std::unique_ptr<ModelInfo> LoadMDLSmartPtr(const char* name, ModelFormat format);
ModelInfo* LoadMDL(const char* name, ModelFormat format);
std::unique_ptr<AnimationFile> LoadANMSmartPtr(const char* name);
void FreeMDL(ModelInfo* pointer);
void FreeAnim(AnimationFile* pointer);
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
bool isTailsAI();
bool isAttacking();

void njRotateXYZ(NJS_MATRIX_PTR m, Angle angx, Angle angy, Angle angz);
bool isKeyboard();
void njAddVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);
void njSubVector(NJS_VECTOR* vd, const NJS_VECTOR* vs);
int __cdecl AdjustAngle(__int16 bams_a, unsigned __int16 bams_b, int limit);
Float njSqrt(Float n);
void SetCharacterAnim_r(uint16_t Index, uint16_t Count, NJS_MOTION* Animation);
void Miles_SetJmpBall(TailsCharObj2* mco2);