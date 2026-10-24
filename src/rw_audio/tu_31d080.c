#include "ps2/prelude.h"

extern s32 func_00312C70(void *);
extern s32 func_0035C544(s32, s32, s32);

void func_0031D080(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x4C);
    if (temp_4 != NULL) {
        func_00312C70(temp_4);
    }
}

void * func_0031D0A8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0035C544(M2C_FIELD(arg0, s32 *, 0x4C) + arg1, arg2, arg3);
    return arg0;
}
