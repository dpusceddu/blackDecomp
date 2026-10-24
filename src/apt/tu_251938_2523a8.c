#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BFAD4;

s32 func_002523A8(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + D_003BFAD4), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002523C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002527C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252828);
