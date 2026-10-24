#include "include_asm.h"

#include "game/effects/runtime.hpp"
extern "C" {long func_001C01E0(void *,void *,int,void *,float);long func_001C1740(void *,void *,int,void *,float);}
struct EffectDispatch{char opaque[0x873f0];void *definition;};

extern "C" long func_001B22D8(EffectDispatch *system,void *data,unsigned short index,void *world,float now){
 char *types=*(char **)((char *)system->definition+0x10);
 unsigned short kind=*(unsigned short *)(types+index*0x34);
 switch(kind){case 1:return func_001C01E0(system,data,index,world,now);case 2:return func_001C1740((char *)system+0x2dc30,data,index,world,now);default:return 0;}
}
