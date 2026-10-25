#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00384F90(void *arg0) {
    return ((u32) M2C_FIELD(arg0, u32 *, 0x58) >> 0x11) & 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/inline/linkonce_384f90", func_00384FA0);
