#include "auto/prelude.h"

void func_00195920(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if ((temp_3 != 0) && (temp_3 != M2C_FIELD(arg0, s32 *, 8))) {
        M2C_FIELD(arg0, s32 *, 8) = temp_3;
    }
}
