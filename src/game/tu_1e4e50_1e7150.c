#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_001E7150(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E7168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E72C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E7448);
