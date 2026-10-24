#include "ps2/prelude.h"

void func_00383E68(void *arg0, s128 *arg1) {
    s16 temp_6;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    temp_6 = M2C_FIELD(temp_3, s16 *, 0x50);
    M2C_FIELD(temp_3, M2C_UNK (**)(void *, s128, s16), 0x54)(arg0 + temp_6, *arg1, temp_6);
}
