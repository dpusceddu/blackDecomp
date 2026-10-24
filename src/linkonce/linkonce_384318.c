#include "ps2/prelude.h"

#include "types_ghidra.h"

s32 func_00384318(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, u32 *, 0);
    M2C_FIELD(arg2, s32 *, 0) = M2C_FIELD(temp_3, s32 (**)(s32), 0x44)(arg0 + M2C_FIELD(temp_3, s16 *, 0x40));
    return arg0;
}
