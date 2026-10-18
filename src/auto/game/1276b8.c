#include "auto/prelude.h"

extern s32 func_00108120();
extern s32 D_0040F4C4;

s32 func_001276B8(void *arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_5;

    temp_5 = arg1 & 0xFF;
    temp_17 = temp_5 * 4;
    if (M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0) == 0) {
        M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0) = func_00108120(D_0040F4C4, M2C_FIELD(((temp_5 * 0x18) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x5844), s32 *, 8)), s64 *, 8));
    }
    return M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0);
}
