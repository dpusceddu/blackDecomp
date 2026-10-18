#include "auto/prelude.h"

extern s32 func_0018DDD8();

void func_0018E2E8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

s32 func_0018E2F0(void *arg0) {
    if (func_0018DDD8(M2C_FIELD(arg0, s32 *, 4) + 0xC94) != 0) {
        M2C_FIELD(arg0, s32 *, 8) = 1;
    } else {
        M2C_FIELD(arg0, s32 *, 8) = 0;
    }
    return 1;
}
