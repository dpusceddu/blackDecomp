#include "auto/prelude.h"

extern s32 func_00317340(void *, M2C_UNK);
extern s32 func_00310768();
extern s32 func_00317340();

void func_00319F80(void *arg0) {
    void *temp_3;

    func_00317340(arg0 + 0x28, 1);
    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x2C) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x2C);
    }
}

s32 func_00319FD0(s32 arg0) {
    M2C_UNK var_17;
    s32 temp_4;
    void *temp_16;

    temp_16 = arg0 + 0x28;
    if (M2C_FIELD(temp_16, u8 *, 0x62) & 2) {
        temp_4 = M2C_FIELD(temp_16, s32 *, 0x38);
        var_17 = 2;
        if (temp_4 != 0) {
            var_17 = (func_00310768(temp_4, 8, 2, 0) == 0) ? 1 : 2;
        }
        func_00317340(temp_16, var_17);
    }
    M2C_FIELD(temp_16, u8 *, 0x62) = (u8) (M2C_FIELD(temp_16, u8 *, 0x62) & 0xDF);
    return arg0;
}

s32 func_0031A058(s32 arg0, s32 *arg1) {
    *arg1 = 0;
    return arg0;
}
