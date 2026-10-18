#include "auto/prelude.h"

extern s32 func_001B37C8(s32, u16);
extern s32 D_0040F4D8;

void func_00152878(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x1BC) != 0xFFFF) {
        func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0x1BC));
    }
}
