#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00110010(void *arg0) {
    return M2C_FIELD(arg0, s64 *, 0x1670) != *M2C_FIELD(arg0, s64 **, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00110028);
