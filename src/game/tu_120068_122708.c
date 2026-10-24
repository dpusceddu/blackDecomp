#include "ps2/prelude.h"

extern s32 func_00107D20(M2C_UNK);

void func_00122708(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = func_00107D20(0x280);
}

s32 func_00122738(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0x15) = 1;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 4) = 300.0f;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1C) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0x1E) = 0x1E;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), f32 *, 0xC) = 20.0f;
    return 1;
}
