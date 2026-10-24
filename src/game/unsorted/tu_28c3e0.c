#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0028C3E0(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028C3E0);

void func_0028C4D8(void) {
    func_0028C3E0(1, 0xFFFF);
}
