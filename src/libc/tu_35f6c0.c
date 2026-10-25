#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035F6C0(void *, s32, s32);
extern void * D_003D6944;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_35f6c0", func_0035F6C0);

void func_003605B8(s32 arg0, s32 arg1) {
    func_0035F6C0(D_003D6944, arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_35f6c0", func_003605E8);
