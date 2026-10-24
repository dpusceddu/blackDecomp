#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00123988();

void func_00123960(void) {
    func_00123988();
}

s32 func_00123980(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00123988);
