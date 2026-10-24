#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_00326B60(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x6A4) = (s32) M2C_FIELD(arg2, s32 *, 0);
    return arg0;
}
