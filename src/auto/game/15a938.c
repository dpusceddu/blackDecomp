#include "auto/prelude.h"

s32 func_0015A938(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0x18) < 1;
}

s32 func_0015A948(void *arg0) {
    if ((M2C_FIELD(arg0, s8 *, 0x20) == 2) || (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), f32 *, 0x20) >= 0.15f)) {
        return 1;
    }
    return 0;
}
