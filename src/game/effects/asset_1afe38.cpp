#include "include_asm.h"

#include "game/effects/mod_asset_views.hpp"
extern "C" {void func_001C6AA0(void *);int func_001C6AB8(void *,unsigned,unsigned);unsigned func_001AFDB8(int);extern unsigned *D_0040F4C0;}

int ModEffects::Regions::Resize(){unsigned width=D_0040F4C0[0],height=D_0040F4C0[1];for(int i=0;i<2;++i){unsigned divider=func_001AFDB8(i);width/=divider;height/=divider;func_001C6AB8(regions+i,width,height);}func_001C6AB8(regions+2,*(unsigned *)this,*((unsigned *)this+1));return 1;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AFEE0);
