#include "auto/prelude.h"

extern void * D_003C9ED4;
extern s32 func_002E91C0();

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
