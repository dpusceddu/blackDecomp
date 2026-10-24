#include "include_asm.h"
#include "ps2/prelude.h"

void func_001F8FF8(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x1B8) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x240) = 1;
    }
    M2C_FIELD(arg0, s32 *, 0x1B8) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9010);
