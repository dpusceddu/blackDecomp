#include "ps2/prelude.h"

extern s32 func_00312C70();

void func_00315180(void *arg0) {
    void *temp_4;

    if (!(M2C_FIELD(arg0, u8 *, 0x18) & 2)) {
        temp_4 = M2C_FIELD(arg0, void **, 0x10);
        if (temp_4 != NULL) {
            func_00312C70(temp_4);
        }
    }
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, void **, 0x10) = NULL;
}
