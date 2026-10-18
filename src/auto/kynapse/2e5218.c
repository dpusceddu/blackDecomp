#include "auto/prelude.h"

extern s32 D_0049B938;
extern s32 func_002E5178();

s32 func_002E5218(void *arg0, void *arg1) {
    s32 *temp_16;
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    temp_16 = temp_4 + (M2C_FIELD(arg1, s32 *, 0) * 4);
    if (*temp_16 == 0) {
        *temp_16 = M2C_FIELD(arg1, s32 (**)(s32), 4)(temp_4);
    }
    M2C_FIELD(arg0, s32 *, 0x14) = *temp_16;
    return 1;
}

void func_002E5278(void) {
    D_0049B938 = 0;
}

void func_002E5288(void) {
    func_002E5178(1, 0xFFFF);
}

void func_002E52A8(void) {
    func_002E5178(0, 0xFFFF);
}
