#include "ps2/prelude.h"

extern s32 func_00172548(f32*);

s32 func_001727C0(f32* self) {
    f32* value;
    s32 count;
    if (!func_00172548(self)) return 0;
    value = (f32*)((u8*)self + 0x4C);
    count = 3;
    do {
        *value = 0.0f;
        count--;
        value--;
    } while (count >= 0);
    return 1;
}
