#include "auto/prelude.h"

void func_001040F8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x20C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x210) = (s32) (arg2 != 0);
}
