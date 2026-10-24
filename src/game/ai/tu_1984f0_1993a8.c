#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00198568();
extern s32 func_00182410();
extern s128 * func_00189478();

void func_001993A8(s32 *arg0) {
    s32 temp_16;

    func_00198568();
    temp_16 = *arg0;
    func_00182410(temp_16 + 0x810, *func_00189478(temp_16 + 0x150), 0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001993F8);
