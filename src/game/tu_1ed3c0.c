#include "ps2/prelude.h"

extern s32 func_00282290();

s32 func_001ED3C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00282290(arg0, arg1, arg2 & 0xFFFF, arg3);
    return 1;
}
