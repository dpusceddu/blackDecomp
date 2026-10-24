#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00275090(s32, s32);
extern s32 D_003BE7A0;

void func_0020DC20(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_5 != 0) {
        func_00275090(D_003BE7A0, temp_5);
        M2C_FIELD(arg0, s32 *, 0) = 0;
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
}
