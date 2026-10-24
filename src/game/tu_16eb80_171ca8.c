#include "ps2/prelude.h"

void func_00171CA8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x20) = arg1;
}

s32 func_00171CB0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x20);
}
