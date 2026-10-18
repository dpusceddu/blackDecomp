#include "auto/prelude.h"

extern void * D_0040F4BC;
extern s32 func_001F2838();
extern s32 D_0040F51C;

void func_0013DC38(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xB9) = 1;
    M2C_FIELD(arg0, s32 *, 0xC4) = (s32) M2C_FIELD(arg0, s32 *, 0x90);
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
}

void func_0013DC50(void *arg0) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 0xC4) != 3) {
        M2C_FIELD(arg0, s8 *, 0xC1) = 0;
    }
    temp_2 = M2C_FIELD(arg0, s32 *, 0x90);
    M2C_FIELD(arg0, s32 *, 0x90) = 3;
    M2C_FIELD(arg0, s32 *, 0xC4) = temp_2;
    M2C_FIELD(arg0, s8 *, 0xB9) = 0;
}

void func_0013DC78(void *arg0) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 0xC4) != 4) {
        M2C_FIELD(arg0, s8 *, 0xC1) = 0;
    }
    temp_2 = M2C_FIELD(arg0, s32 *, 0x90);
    M2C_FIELD(arg0, s32 *, 0x90) = 4;
    M2C_FIELD(arg0, s32 *, 0xC4) = temp_2;
    M2C_FIELD(arg0, s8 *, 0xB9) = 0;
}

void func_0013DCA0(void *arg0) {
    void *temp_2;

    if (M2C_FIELD(arg0, u8 *, 0xB9) != 0) {
        if (M2C_FIELD(D_0040F4BC, u8 *, 0x1678) != 0) {
            func_001F2838(D_0040F51C, 0, 1);
        } else {
            func_001F2838(D_0040F51C, 0, 5);
        }
    }
    temp_2 = M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(temp_2, f32 *, 0x4F8);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(temp_2, f32 *, 0x4FC);
}
