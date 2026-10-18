#include "auto/prelude.h"

void func_00106FE8(void *arg0, s32 arg1, s64 arg2) {
    M2C_FIELD(arg0, s64 *, 0x28) = arg2;
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 4);
}

void func_00107000(void *arg0, s64 arg1) {
    M2C_FIELD(arg0, s64 *, 0x30) = arg1;
}

s64 func_00107008(void *arg0) {
    return M2C_FIELD(arg0, s64 *, 0x30);
}

void func_00107010(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x778) = 1;
}
