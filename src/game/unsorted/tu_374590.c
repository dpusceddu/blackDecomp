#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_00374590(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0x224) & 0x8000);
    return arg0;
}

s32 func_003745A8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x1A8);
    return arg0;
}
