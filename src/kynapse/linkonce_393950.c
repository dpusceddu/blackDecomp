#include "ps2/prelude.h"

extern s32 func_002FB6D8();

s32 func_00393950(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002FB6D8(M2C_FIELD(arg0, s32 *, 0x64), arg1, arg2 & 0xFF, arg3 & 0xFF);
}
