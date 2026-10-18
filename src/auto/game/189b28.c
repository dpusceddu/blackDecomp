#include "auto/prelude.h"

extern s32 * func_00179258();
extern s32 D_0040F4D4;
extern s128 * func_00178D30();

void func_00189B28(void *arg0, void *arg1) {
    s32 *temp_4;

    temp_4 = func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(arg1, s32 *, 0));
    M2C_FIELD(arg1, s8 *, 5) = 1;
    M2C_FIELD(arg1, s128 *, 0x20) = (s128) *func_00178D30(temp_4);
    M2C_FIELD(arg1, s128 *, 0x30) = (s128) M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), void **, 0x7C), s128 *, 0xA0);
}
