#include "auto/prelude.h"

void func_00109550(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1A8);
    M2C_FIELD(arg0, s8 *, 0x1B8) = 0;
    if ((temp_3 != 0x37) && (temp_3 != 1)) {
        M2C_FIELD(arg0, s8 *, 0x1B9) = 1;
    }
}

s32 func_00109578(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x1A8) == 0x1C;
}
