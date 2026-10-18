#include "auto/prelude.h"

extern s32 func_002E5E58();

s32 func_002E71E0(void *arg0) {
    s32 temp_2;

    temp_2 = func_002E5E58();
    if (temp_2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + 1);
    }
    return temp_2;
}
