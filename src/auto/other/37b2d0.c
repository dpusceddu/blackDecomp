#include "auto/prelude.h"

extern s32 func_0037B988();
extern s32 func_003230C0();

s32 func_0037B2D0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_0037B988(arg0, arg1, M2C_FIELD(arg2, s32 *, 4));
    return func_003230C0((s32) temp_2, M2C_FIELD(temp_2, s32 *, 0x80), 2, arg2);
}
