#include "auto/prelude.h"

void func_00392DB0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}

s32 func_00392DB8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}
