#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0014F490(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x118);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014F498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014F668);

void func_0014F6F0(void *arg0, s32 arg1) {
    if (arg1 == 0) {
        M2C_FIELD(arg0, s8 *, 0x155) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014F708);
