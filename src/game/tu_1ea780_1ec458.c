#include "include_asm.h"
#include "ps2/prelude.h"

void func_001EC458(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EC470);
