#include "auto/prelude.h"

s32 func_00268E90(void *arg0, s32 arg1) {
    return M2C_FIELD(arg0, s32 *, 0x114) + (arg1 << 6);
}

void func_00268EA0(void *arg0) {
    s16 temp_6;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    temp_6 = M2C_FIELD(temp_3, s16 *, 0x30);
    M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK, s16), 0x34)(arg0 + temp_6, 0, temp_6);
}
