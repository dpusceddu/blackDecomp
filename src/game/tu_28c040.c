#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0028C040(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028C040);

void func_0028C3A0(void) {
    func_0028C040(1, 0xFFFF);
}

void func_0028C3C0(void) {
    func_0028C040(0, 0xFFFF);
}
