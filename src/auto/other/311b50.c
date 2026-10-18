#include "auto/prelude.h"

extern s32 func_00312C70();

s32 func_00311B50(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_3 != 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = (s32) (temp_3 - 1);
        return 0;
    }
    *M2C_FIELD(arg0, void ***, 0x18) = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x18);
    if (!(M2C_FIELD(arg0, s32 *, 0x10) & 1)) {
        func_00312C70(arg0, arg0);
    }
    return 1;
}
