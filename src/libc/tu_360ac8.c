#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00360AF0();
extern void * D_003D6944;

s32 func_00360AC8(s32 arg0, s32 arg1) {
    return func_00360AF0(arg0, arg1, (s32) (D_003D6944 + 0x5C));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_360ac8", func_00360AF0);
