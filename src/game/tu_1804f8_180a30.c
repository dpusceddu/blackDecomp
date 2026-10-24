#include "include_asm.h"
#include "ps2/prelude.h"

f32 func_00180A30(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x100), f32 *, 0x10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180A48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180AA0);
