#include "auto/prelude.h"

extern s32 func_0035D728();
extern s32 func_0035CBC0();

void func_001094C0(void *arg0, M2C_UNK *arg1, s32 arg2, s32 arg3) {
    s32 temp_4;

    func_0035D728(arg0 + 0x44, "videos/%s.m2v", arg1);
    func_0035CBC0(arg0 + 0x84, arg1);
    temp_4 = M2C_FIELD(arg0, s32 *, 0x1A8);
    M2C_FIELD(arg0, s32 *, 0x198) = arg3;
    M2C_FIELD(arg0, s8 *, 0x1B8) = 1;
    M2C_FIELD(arg0, s32 *, 0x1B4) = arg2;
    if ((temp_4 != 0x37) && (temp_4 != 1)) {
        M2C_FIELD(arg0, s8 *, 0x1B9) = 1;
    }
}
