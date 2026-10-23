#include "auto/prelude.h"

void func_00274F58(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}

s32 func_00274F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00274F70(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0x10);
}
