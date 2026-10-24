#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0032B9E0();
extern s32 func_0032B9E0(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032B928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032B9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032BB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032BC18);

void func_0032BC30(void) {
    func_0032B9E0(1, 0xFFFF);
}

void func_0032BC50(void) {
    func_0032B9E0(0, 0xFFFF);
}
