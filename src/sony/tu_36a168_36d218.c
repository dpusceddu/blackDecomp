#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0036CFF0();

s32 func_0036D218(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    return func_0036CFF0(arg0, arg1, arg2, (s32) sp, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036D238);
