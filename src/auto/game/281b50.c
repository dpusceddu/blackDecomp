#include "auto/prelude.h"

void * func_00281B50(void *arg0) {
    s32 temp_2;
    s32 temp_2_2;
    void *var_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x182C);
    var_3 = NULL;
    if (temp_2 != 0) {
        temp_2_2 = temp_2 - 1;
        M2C_FIELD(arg0, s32 *, 0x182C) = temp_2_2;
        var_3 = (M2C_FIELD((arg0 + temp_2_2), u8 *, 0x17C4) * 0x38) + arg0;
    }
    return var_3;
}
