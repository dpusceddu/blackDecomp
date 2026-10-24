#include "ps2/prelude.h"

extern void * D_0040F0E0;
extern s32 func_0026BBC0();
extern s32 func_001249F8();
extern s32 func_00103870();
extern void * D_0040F4BC;
extern s32 func_00103800();
extern s32 func_0020F920(s32);
extern s32 func_002105F8(s32);
extern s32 func_00107D20(M2C_UNK);

void func_00121B40(void) {
    void *temp_16;

    temp_16 = M2C_FIELD(D_0040F0E0, void **, 0x21060);
    if (func_0026BBC0(M2C_FIELD(temp_16, s32 *, 0xC), func_001249F8(temp_16, 0x19)) & 0xFF) {
        if ((func_00103870(D_0040F0E0) == 0) && (M2C_FIELD(D_0040F4BC, u8 *, 0x1678) == 0)) {
            func_00103800(D_0040F0E0, 1);
        }
    }
}

s32 func_00121BD0(s32 arg0) {
    func_0020F920(arg0 + 8);
    func_002105F8(arg0 + 0xC);
    return 1;
}

void func_00121C08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = func_00107D20(0x40);
}
