#include "auto/prelude.h"

s32 func_0015C920(void *arg0, s8 arg1) {
    s32 var_2;
    s8 *temp_2;
    s8 *temp_4_2;
    s8 var_3;
    s8 var_6;
    void *temp_4;

    if (M2C_FIELD(arg0, u8 *, 0x45) == 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x20);
        var_3 = 0x7F;
        temp_2 = M2C_FIELD(temp_4, s8 **, 0);
        var_6 = 0x7F;
        if (temp_2 != NULL) {
            var_3 = *temp_2;
        }
        temp_4_2 = M2C_FIELD(temp_4, s8 **, 4);
        if (temp_4_2 != NULL) {
            var_6 = *temp_4_2;
        }
        var_2 = 0;
        if (arg1 != var_3) {
            var_2 = 1;
            if (arg1 == var_6) {
                goto block_7;
            }
        }
    } else {
block_7:
        var_2 = 0;
    }
    return var_2;
}
