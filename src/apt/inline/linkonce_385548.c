#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00385548(void *arg0) {
    return ((u32) M2C_FIELD(arg0, u32 *, 0x1C) >> 8) & 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/inline/linkonce_385548", func_00385558);
