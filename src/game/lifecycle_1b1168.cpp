#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}
int ModEffects::Entry::Initialize(const Matrix *matrix,char *asset,unsigned char enabled,float now){resource=asset;started=now;world=*matrix;flags=enabled;return 1;}
