#include "auto/prelude.h"

extern s32 func_002E4C60();
extern void * D_003C9ED4;
extern u32 D_003C9594;

void func_002E9D10(s32 arg0, void *arg1) {
    u32 temp_2;

    temp_2 = func_002E4C60(arg1);
    if (temp_2 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10)) {
        D_003C9594 = temp_2;
    }
}
