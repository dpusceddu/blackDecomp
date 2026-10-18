#include "auto/prelude.h"

extern u32 func_002ECAA8();
extern void * D_003C9ED4;
extern f32 D_003C958C;

void func_002E98F0(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_6;

    temp_6 = func_002ECAA8(arg2);
    if ((arg1 >= 0) && ((u32) arg1 < (u32) M2C_FIELD(arg0, u32 *, 4)) && (temp_6 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x18))) {
        M2C_FIELD(((arg1 * 4) + M2C_FIELD(((temp_6 * 0xC) + M2C_FIELD(arg0, s32 *, 0x38)), s32 *, 8)), f32 *, 0) = D_003C958C;
    }
}
