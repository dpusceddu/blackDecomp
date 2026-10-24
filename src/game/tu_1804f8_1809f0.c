#include "ps2/prelude.h"

s32 func_001809F0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x100), s32 *, 0x18);
}

s128 func_00180A00(void *arg0) {
    return *M2C_FIELD(arg0, s128 **, 0x100);
}
