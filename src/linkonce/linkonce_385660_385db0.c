#include "ps2/prelude.h"

extern s32 func_002520D8(s32, s32, s32);
extern s32 func_0024FA38(s32, M2C_UNK);
extern s32 D_0043DEE4;

void func_00385DB0(s32 arg0, s32 arg1) {
    func_002520D8(func_0024FA38(D_0043DEE4, 0x34), arg0, arg1);
}

s32 func_00385E00(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x38);
}

s32 func_00385E08(void) {
    return 0;
}

s32 func_00385E10(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}

s32 func_00385E18(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34);
}
