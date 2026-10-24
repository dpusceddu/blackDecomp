#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B1080();

s32 func_001C1548(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    func_001B1080(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1570);
