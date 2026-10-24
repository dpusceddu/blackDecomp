#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00316400(s32, s32);

s32 func_0031E5A0(s32 arg0, s32 *arg1, s32 arg2) {
    return func_00316400(*arg1, arg2) == 0;
}
