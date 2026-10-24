#include "ps2/prelude.h"

extern s32 func_003110B0(s32, M2C_UNK, M2C_UNK);
extern s32 func_002803F8();

void func_00282C18(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x70);
    if (temp_4 != 0) {
        func_003110B0(temp_4, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x70) = 0;
    }
    func_002803F8(arg0);
}
