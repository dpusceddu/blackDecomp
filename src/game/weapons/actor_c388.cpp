#include "include_asm.h"

#include "game/weapons/projectile_lifetime.hpp"
namespace ActorParts {
extern "C" {
void func_0014BA80(void*,float);long func_0014FBE8(void*,float);void func_001EA580(void*,unsigned long,int);void func_00155C28(void*,void*,unsigned char,unsigned char);
extern ExpiryWorld*D_0040F4D0;extern ExpiryServiceWorld*D_0040F510;extern void*D_0040F520;extern float D_004146D0;extern int D_004146D4;
}

void ExpiryEffect::Update(float dt){
 if(!D_004146D4){float initial=D_0040F4D0->delay;D_004146D4=1;D_004146D0=-initial;}
 func_0014BA80(this,dt);long result=func_0014FBE8(this,dt);remaining-=dt;
 if(remaining<0.25f&&flag1==1)func_001EA580(D_0040F510->services->events,0x684BBB0484A09400UL,1);
 if(remaining<D_004146D0&&!result){func_00155C28(D_0040F520,this,flag1,flag2);func_001EA580(D_0040F510->services->events,0x66CCFC6DDB243000UL,0);}
}
}

// Unmatched: 0x14FBE8 matrix-copy and vector/FPU operand order after reference-lifetime recovery.

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014FBE8);
