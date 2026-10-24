#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AE130(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AE130);

void func_001AE2C8(void) {
    func_001AE130(1, 0xFFFF);
}
