#include "include_asm.h"
#include "ps2/prelude.h"

void func_00244CD8(s32 *arg0) {
    *arg0 += 1;
}

void func_00244CE8(s32 *arg0) {
    *arg0 -= 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00244CF8);
