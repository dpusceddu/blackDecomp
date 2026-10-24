#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001106B8(void *, u32, s32, f32, f32);

s32 func_00110698(void *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    return func_001106B8(arg0, (u32) arg1, arg2, fparg0, 0.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001106B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00110850);
