#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_3605f0", func_003605F0);

#include "ps2/recovered_types.h"
extern s32 func_003605F0(s32, void *, void *, s32);
extern void * D_003D6944;

s32 func_00360800(void *arg0, void *arg1, s32 arg2) {
    return func_003605F0((s32) D_003D6944, arg0, arg1, arg2);
}
