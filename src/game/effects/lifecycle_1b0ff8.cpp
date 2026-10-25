#include "include_asm.h"

#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}

void Effects::Child::Clear(){IdentityXYZ(world);resource=0;parent=0;time=0;started=0;}
