#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00291000(void *, s32, s32);

s32 func_00291C38(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = arg1;
    *(s32 *)(sp + 8) = arg2;
    *(s64 *)(sp + 16) = (s64) arg3;
    return func_00291000(sp, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291E90);

#include "ps2/recovered_types.h"
extern s32 func_00291CC0(void *, s32, s32);

s32 func_00291F28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = arg1;
    *(s32 *)(sp + 8) = arg2;
    *(s32 *)(sp + 12) = arg3;
    return func_00291CC0(sp, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00291F58);
