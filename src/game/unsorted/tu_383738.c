#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00383738(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00383750);
