#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern void func_00367C90(); /* Deci2Call */

void func_0036EAE0(s32 arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = (s32) arg1;
    func_00367C90(3, sp);
}

void func_0036EB10(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    func_00367C90(4, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036EB38);
