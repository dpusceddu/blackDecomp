#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001437D8(void *);
extern void * D_0040F540;

s32 func_00138970(void) {
    return func_001437D8(D_0040F540) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_138970", func_00138998);
