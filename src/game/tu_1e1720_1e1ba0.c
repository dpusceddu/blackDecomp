#include "ps2/prelude.h"

extern s32 func_0035C6EC(s32, M2C_UNK, M2C_UNK);
extern s32 func_001E1EB8();

s32 func_001E1BA0(void *arg0) {
    func_0035C6EC(arg0 + 0x20, 0, 0x28);
    M2C_FIELD(arg0, s32 *, 0x5C) = 7;
    return 1;
}

void func_001E1BE0(void *arg0, s128 arg1, f32 fparg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x58);
    if (temp_2 != NULL) {
        M2C_FIELD(arg0, s128 *, 0x10) = arg1;
        if (M2C_FIELD(temp_2, u8 *, 0xAC) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x5C) == 2) {
                func_001E1EB8();
            }
            M2C_FIELD(arg0, s8 *, 0x7C) = 1;
        } else {
            M2C_FIELD(arg0, s8 *, 0x79) = 1;
        }
        M2C_FIELD(arg0, f32 *, 0x64) = fparg0;
    }
}
