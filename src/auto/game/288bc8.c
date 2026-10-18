#include "auto/prelude.h"

extern s32 func_00289398();

s32 func_00288BC8(s32 arg0) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_2 != 0) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (temp_2 + arg0);
    }
    temp_2_2 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_2_2 != 0) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_2_2 + arg0);
    }
    temp_2_3 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_2_3 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_2_3 + arg0);
    }
    return func_00289398(M2C_FIELD(arg0, s32 *, 4));
}
