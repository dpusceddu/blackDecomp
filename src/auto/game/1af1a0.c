#include "auto/prelude.h"

s32 func_001AF1A0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    return 1;
}

void func_001AF1B8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
}
