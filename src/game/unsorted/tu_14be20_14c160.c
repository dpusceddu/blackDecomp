#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0014C088(s64 *, s32);

s32 func_0014C160(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_0014C088(arg0, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014C180);
