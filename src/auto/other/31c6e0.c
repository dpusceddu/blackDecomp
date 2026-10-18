#include "auto/prelude.h"

u32 func_0031C6E0(void *arg0) {
    s32 temp_5;
    u32 var_2;
    void *temp_6;

    temp_6 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xA8), void **, 0x90);
    temp_5 = M2C_FIELD(temp_6, s32 *, 0);
    if ((temp_5 != 3) && (temp_5 != 1)) {
        var_2 = M2C_FIELD(temp_6, u32 *, 0x14);
    } else {
        var_2 = M2C_FIELD(arg0, u32 *, 0x64);
    }
    return var_2 / (u32) M2C_FIELD(arg0, u32 *, 0xB4);
}
