#include "include_asm.h"

#include "game/effects/render_state.h"
extern int func_001B0910(void *);

int func_001AE998(BkActorRenderPS2 *actor,int index) {
 void *buffer=0;
 switch(index){case 0:buffer=&actor->buffers[0];break;case 1:buffer=&actor->buffers[1];break;case 2:buffer=&actor->buffers[2];break;}
 return func_001B0910(buffer);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AEA18);
