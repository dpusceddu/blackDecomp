#include "auto/prelude.h"

s32 func_00136BA8(void *arg0, void *arg1, s16 arg2) {
    return M2C_FIELD(arg0, s32 *, 0x354) + M2C_FIELD(((arg2 * 6) + M2C_FIELD(arg1, s32 *, 0x20)), s16 *, 0);
}
