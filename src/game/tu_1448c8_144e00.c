#include "auto/prelude.h"

extern s32 func_001B6CF8(s32, s32, M2C_UNK);
extern s32 D_0040F4D8;
extern s32 func_00149AC8(s32);

s32 func_00144E00(s32 arg0) {
    func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 0);
    func_00149AC8(arg0);
    return 1;
}
