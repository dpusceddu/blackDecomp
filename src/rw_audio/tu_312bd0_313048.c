#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern void * func_00311398(void *, s32);
extern void * func_00311430(void *, void *, s32);
extern s32 D_0040E154;
extern s32 D_0040E150;

void * func_00313048(void *arg0, void *arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_00311398(func_00311430(arg0, arg1, arg2), 0);
    D_0040E154 = 0;
    D_0040E150 += 1;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003130A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313148);
