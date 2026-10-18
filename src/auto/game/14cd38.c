#include "auto/prelude.h"

s32 func_0014CD38(s32 arg0) {
    s32 temp_5;
    void *temp_2;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x38);
    temp_2 = M2C_FIELD(arg0, s32 *, 0x2C) + (temp_5 * 0x50);
    M2C_FIELD(temp_2, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) + (temp_5 * 0x9D0));
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) + 1);
    return (s32) temp_2;
}
