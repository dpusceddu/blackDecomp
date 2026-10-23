#include "auto/prelude.h"

extern s32 func_00242260();
extern s32 func_00242408();

s32 func_00242778(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;
    s32 temp_18;
    u32 temp_19;

    temp_17 = ((u32) arg1 >> 0xA) & 0x7F;
    temp_18 = ((u32) arg1 >> 2) & 0xFF;
    temp_19 = (u32) arg1 >> 0x11;
    func_00242260(arg0, (s32) temp_19, temp_17, arg1, temp_18, arg2);
    return func_00242408(arg0, (s32) temp_19, temp_17, arg1, temp_18);
}
