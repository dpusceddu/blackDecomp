#include "auto/prelude.h"

s32 func_0015D210(void **arg0, s32 arg1) {
    return M2C_FIELD(*arg0, s32 *, 4) + ((s32) (arg1 << 0x18) >> 0x13);
}

s32 func_0015D228(void **arg0, s32 arg1) {
    return M2C_FIELD((((s32) (arg1 << 0x18) >> 0x13) + M2C_FIELD(*arg0, s32 *, 4)), s32 *, 8);
}
