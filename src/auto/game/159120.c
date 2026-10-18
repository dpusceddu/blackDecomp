#include "auto/prelude.h"

extern s32 func_001E1A70(s32);
extern s32 func_001E2C38(s32, s32);
extern void * D_0040F510;

void func_00159120(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_4 != 0) {
        func_001E1A70(temp_4);
    }
}

s32 func_00159148(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_5 != 0) {
        func_001E2C38(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x14), temp_5);
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
    return 1;
}
