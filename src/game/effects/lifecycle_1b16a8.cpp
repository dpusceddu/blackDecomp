#include "include_asm.h"

#include "game/effects/runtime.hpp"
extern "C" {void func_001B1110(void *,void *);int func_001B1138(void *);void func_001B1648(void *,void *);}

int ModEffects::Entry::Active(){for(unsigned short i=0;i<8;++i){Child *child=children[i];if(child!=(Child*)1){if(!child)return 0;if(func_001B1138(child))return 1;}}return 0;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B1728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B1848);
