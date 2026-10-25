#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00341D20(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_341d20", func_00341D20);

void func_003420A8(void) {
    func_00341D20(1, 0xFFFF);
}

void func_003420C8(void) {
    func_00341D20(0, 0xFFFF);
}
