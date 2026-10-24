#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001EFFC8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EFFC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F02C8);

void func_001F0300(void) {
    func_001EFFC8(1, 0xFFFF);
}
