#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037C048(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37c048", func_0037C048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37c048", func_0037C190);

s32 func_0037C1F0(s32 *arg0) {
    return *arg0;
}

void func_0037C1F8(void) {
    func_0037C048(1, 0xFFFF);
}

void func_0037C218(void) {
    func_0037C048(0, 0xFFFF);
}
