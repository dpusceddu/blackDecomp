#include "auto/prelude.h"

extern s32 func_00274E68();

s32 func_00107A08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0x1C) = arg2;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    return func_00274E68(arg0, arg1, arg3);
}
