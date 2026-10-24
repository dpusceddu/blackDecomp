#include "ps2/prelude.h"

extern s32 func_0012BD98();

s8 func_0012BDC8(void) {
    void *temp_2;

    temp_2 = func_0012BD98();
    if (temp_2 == NULL) {
        return -1;
    }
    return M2C_FIELD(temp_2, s8 *, 0x39);
}

void func_0012BDF0(void *arg0, s32 arg1) {
    s32 temp_6;

    temp_6 = M2C_FIELD(arg0, s32 *, 0x5AB0);
    if ((temp_6 != M2C_FIELD(M2C_FIELD(arg0, void **, 0x5AB4), u8 *, 0x11)) && (temp_6 == (arg1 - 1))) {
        M2C_FIELD(arg0, s32 *, 0x5AA8) = 1;
    }
}
