#include "auto/prelude.h"

extern s32 func_0011D490();
extern void * func_0011D498(void **arg0);
extern s32 func_00136E88(void *, M2C_UNK);
extern s32 func_0025C4C8(s32, s32);
extern s32 D_0040F4CC;

void func_0011FC80(void **arg0) {
    void *temp_2;

    func_0011D490();
    temp_2 = func_0011D498(arg0);
    if (M2C_FIELD(temp_2, s32 *, 0x350) != 0) {
        func_00136E88(temp_2, 0);
        func_0025C4C8(D_0040F4CC, M2C_FIELD(arg0, s32 *, 0x50));
    }
    M2C_FIELD(arg0, s8 *, 0x58) = 0;
}
