#include "ps2/prelude.h"

extern f32 func_003106F0(s32, M2C_UNK, M2C_UNK);

void func_00284A60(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x7C) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1);
    }
}

void func_00284A98(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x80) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1);
    }
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
}
