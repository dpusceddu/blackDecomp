#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037F050(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37f050", func_0037F050);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37f050", func_0037F198);

void func_0037F238(void) {
    func_0037F050(1, 0xFFFF);
}

void func_0037F258(void) {
    func_0037F050(0, 0xFFFF);
}
