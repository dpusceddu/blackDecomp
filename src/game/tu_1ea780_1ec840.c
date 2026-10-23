#include "auto/prelude.h"

s32 func_001EC840(void *arg0, s32 arg1, s32 arg2) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x1E10), s32 *, 0x18) + (arg2 * 8);
}
