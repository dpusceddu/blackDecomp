#include "auto/prelude.h"

extern s32 func_00165AE0();

void func_001749C8(void) {
    func_00165AE0();
}

s32 func_001749E8(void *arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, s64 *, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 0x18) = arg4;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    return 1;
}
