#include "auto/prelude.h"

s32 func_001BEC68(s32 arg0) {
    s32 *temp_3;
    u32 var_3;
    u32 var_4;
    void *temp_2;
    void *temp_5;

    var_3 = 0;
    do {
        temp_2 = (var_3 * 0x130) + arg0;
        M2C_FIELD(temp_2, s8 *, 0x124) = 0;
        var_4 = 0;
        temp_5 = temp_2 + 0xB0;
loop_2:
        temp_3 = temp_5 + (var_4 * 4);
        var_4 = (var_4 + 1) & 0xFFFF;
        *temp_3 = 0;
        if (var_4 < 8U) {
            goto loop_2;
        }
        var_3 = (var_3 + 1) & 0xFFFF;
        M2C_FIELD(temp_5, s32 *, 0x60) = 0;
    } while (var_3 < 0x2CU);
    return 1;
}

s32 func_001BECC8(void) {
    return 1;
}
