#include "auto/prelude.h"

s128 func_00183558(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0xC4) == 2) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s128 *, 0x30);
    }
    return M2C_FIELD(arg1, s128 *, 0xA0);
}
