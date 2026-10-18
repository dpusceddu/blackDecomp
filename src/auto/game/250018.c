#include "auto/prelude.h"

s32 func_00250018(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 + 8;
}

s32 func_00250038(s32 arg0, void *arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg1, s32 *, -8);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 + 8;
}
