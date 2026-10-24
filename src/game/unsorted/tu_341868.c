#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00341868();
extern s32 func_00341868(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00341868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003419B0);

void func_003419C0(void) {
    func_00341868(1, 0xFFFF);
}

void func_003419E0(void) {
    func_00341868(0, 0xFFFF);
}
