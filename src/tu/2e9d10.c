#include "auto/prelude.h"

extern s32 func_002E4C60();
extern void * D_003C9ED4;
extern u32 D_003C9594;
extern s32 func_002E91C0();

void func_002E9D10(s32 arg0, void *arg1) {
    u32 temp_2;

    temp_2 = func_002E4C60(arg1);
    if (temp_2 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10)) {
        D_003C9594 = temp_2;
    }
}

void func_002E9D50(s32 arg0, f32 fparg0) {
    if ((arg0 >= 0) && ((u32) arg0 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10))) {
        M2C_FIELD(((arg0 * 0x18) + M2C_FIELD(func_002E91C0(), s32 *, 0x34)), f32 *, 0xC) = fparg0;
    }
}

f32 func_002E9DB8(s32 arg0) {
    if ((arg0 < 0) || ((u32) arg0 >= (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10))) {
        return 0.0f;
    }
    return M2C_FIELD(((arg0 * 0x18) + M2C_FIELD(func_002E91C0(), s32 *, 0x34)), f32 *, 0xC);
}
