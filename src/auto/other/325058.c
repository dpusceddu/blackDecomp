#include "auto/prelude.h"

extern s32 func_003680A0();
extern s32 func_003242B0();

s32 func_00325058(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;

    temp_17 = arg2 * 0x24;
    func_003680A0(arg0, (arg0 + temp_17) - 1);
    return func_003242B0(arg1, arg0, temp_17, 0x48, 0, 0, arg1, arg2);
}
