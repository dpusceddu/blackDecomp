#include "ps2/prelude.h"

void func_0016EA80(void *arg0) {
    s32 var_3;

    var_3 = 0;
    if (M2C_FIELD(arg0, s32 *, 8) > 0) {
        do {
            M2C_FIELD((M2C_FIELD(arg0, s32 *, 4) + var_3), s8 *, 0) = 0;
            var_3 += 1;
        } while (var_3 < M2C_FIELD(arg0, s32 *, 8));
    }
}

void func_0016EAB8(s32 *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(((arg1 * 4) + *arg0), s32 *, 0) = arg2;
}
