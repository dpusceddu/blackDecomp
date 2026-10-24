#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}
void ModEffects::RecordSet::Clear(){Pair *p=pairs;for(signed char i=0;i<2;++i,++p){p->record=0;p->count=0;}}
