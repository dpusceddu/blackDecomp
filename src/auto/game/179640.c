#include "auto/prelude.h"

s32 func_00179640(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x70) != 0;
}

void * func_00179650(void *arg0, s32 arg1) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x70), s32 *, 0x2C) + (arg1 * 0x50);
}
