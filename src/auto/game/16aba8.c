#include "auto/prelude.h"

void func_0016ABA8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 > 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) = arg1;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 4) = arg2;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 8) = arg3;
        M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + 1);
    }
}
