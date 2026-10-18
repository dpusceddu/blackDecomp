#include "auto/prelude.h"

extern s32 func_001580E0();
extern s32 * func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00162580();

void func_001886E0(void *arg0) {
    s32 temp_18;
    s32 temp_5;

    temp_18 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), void **, 0x7C), s32 *, 0x2A4);
    if (func_001580E0(temp_18) < M2C_FIELD(arg0, s32 *, 0x20)) {
        temp_5 = M2C_FIELD(arg0, s32 *, 8);
        if ((temp_5 != -1) && (M2C_FIELD(func_00179258(D_0040F4D4 + 0xFA8, temp_5), s32 *, 4) == 1)) {
            func_00162580(M2C_FIELD(func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(arg0, s32 *, 8)), s32 *, 8));
        }
        M2C_FIELD(arg0, s32 *, 0x20) = func_001580E0(temp_18);
    }
}
