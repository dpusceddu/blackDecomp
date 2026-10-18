#include "auto/prelude.h"

extern s32 func_00165AE0();
extern void * func_00135550();
extern s32 func_0018D3A0();

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

void func_00174A00(s32 arg0, s64 *arg1) {
    s32 temp_17;

    if (arg1 != NULL) {
        temp_17 = M2C_FIELD(arg1, s32 *, 0xC4);
        if ((temp_17 == 1) && (func_00135550(arg1) != NULL) && (M2C_FIELD(func_00135550(arg1), s32 *, 0x80) == temp_17)) {
            func_0018D3A0(func_00135550(arg1) + 0xD10, arg0);
        }
    }
}
