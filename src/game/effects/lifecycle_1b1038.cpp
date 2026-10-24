#include "include_asm.h"

#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}

int ModEffects::Child::Initialize(void *object,Entry *owner,const Matrix *matrix,float now){resource=object;parent=owner;world=*matrix;time=now;started=now;return 1;}
