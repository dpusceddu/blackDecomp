#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00332B68();
extern s32 func_00332B68(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_332b68", func_00332B68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_332b68", func_00332CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_332b68", func_00332D28);

void func_00332D48(void) {
    func_00332B68(1, 0xFFFF);
}

void func_00332D68(void) {
    func_00332B68(0, 0xFFFF);
}
