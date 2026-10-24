#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00151B40();

void func_00152988(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        if ((u32) M2C_FIELD(arg0, u32 *, 0x1B4) >= 2U) {
            if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xB4), u8 *, 0x3D) == 0) {
                goto block_4;
            }
        } else {
block_4:
            func_00151B40(arg0, 1, 1);
        }
    }
}
