#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00100288(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x60);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100318);
