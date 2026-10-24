#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037D880(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037D880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037D9C8);

void func_0037DEF0(void) {
    func_0037D880(1, 0xFFFF);
}

void func_0037DF10(void) {
    func_0037D880(0, 0xFFFF);
}
