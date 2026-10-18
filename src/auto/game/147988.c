#include "auto/prelude.h"

void * func_00147988(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 0x1A4)), s32 *, 0);
    if (temp_2 >= 0) {
        return M2C_FIELD(arg0, s32 *, 0x19C) + (temp_2 << 6);
    }
    return arg0 + 0x70;
}
