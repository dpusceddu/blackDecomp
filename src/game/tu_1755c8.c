#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001749E8();

s32 func_001755C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 9, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x2C) = arg2;
    M2C_FIELD(arg0, s8 *, 0x29) = -1;
    M2C_FIELD(arg0, s8 *, 0x28) = 0;
    return 1;
}
