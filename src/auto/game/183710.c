#include "auto/prelude.h"

s32 func_00183710(void *arg0, s8 arg1) {
    if ((arg1 >= 0) && (arg1 < M2C_FIELD(arg0, s32 *, 8))) {
        return M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0);
    }
    return 0;
}
