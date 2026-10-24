#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}
int ModEffects::Child::Reset(){if(parent)func_001B1648(parent,this);IdentityXYZ(world);resource=0;parent=0;time=0;started=0;return 1;}
