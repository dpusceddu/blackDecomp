#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_00455F58;

s32 func_00311498(void *arg0, void *arg1) {
    s32 temp_3;

    if (M2C_FIELD(arg0, s32 *, 0) == M2C_FIELD(arg1, s32 *, 0)) {
        temp_3 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_3 & 4) {
            M2C_FIELD(arg1, s32 *, 4) = temp_3;
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003114C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003114D0);

M2C_UNK * func_00311558(void) {
    return &D_00455F58;
}
