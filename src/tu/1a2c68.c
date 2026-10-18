#include "auto/prelude.h"

extern u8 func_0016DFB0(s32, f32);
extern s32 D_0040F4D4;

s32 func_001A2C68(void) {
    return 0;
}

void func_001A2C70(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x58) = func_0016DFB0(D_0040F4D4, M2C_FIELD(arg0, f32 *, 0x5C));
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x29C) == 3) {
        M2C_FIELD(arg0, u8 *, 0x58) = 1U;
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x694), s8 *, 0x3D) = (s8) (M2C_FIELD(arg0, u8 *, 0x58) ^ 1);
}
