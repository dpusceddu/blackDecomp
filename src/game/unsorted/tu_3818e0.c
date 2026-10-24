#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003818E0(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003818E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00381A28);

void func_00381A70(void) {
    func_003818E0(1, 0xFFFF);
}

void func_00381A90(void) {
    func_003818E0(0, 0xFFFF);
}
