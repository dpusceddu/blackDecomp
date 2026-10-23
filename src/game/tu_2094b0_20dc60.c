#include "auto/prelude.h"

extern s32 func_0020DC20();
extern s32 func_0020DB90(s32 *, s32);
extern s32 func_0020DB90();
extern s32 func_0027C278(s32);
extern s32 func_00209F38();
extern s32 func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209FF8();
extern s32 func_00275340();
extern s32 func_00275398();
extern s32 func_00275260();
extern s32 func_0020DE78();

void func_0020DC60(s32 *arg0, s32 arg1) {
    s32 temp_17;

    temp_17 = arg1 + 1;
    if (*arg0 < temp_17) {
        func_0020DC20();
        func_0020DB90(arg0, temp_17);
    }
}

s32 func_0020DCB0(s32 arg0) {
    M2C_FIELD(arg0, s16 **, 4) = NULL;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = -1;
    func_0020DB90(arg0, 0x10);
    *M2C_FIELD(arg0, s16 **, 4) = 0;
    return 1;
}

void func_0020DCF8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = func_0027C278(arg1);
    func_00209F38(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s32 *, 4));
}

void func_0020DD48(void *arg0) {
    func_00209FF8(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8));
}

void func_0020DD88(void *arg0) {
    *M2C_FIELD(arg0, s16 **, 4) = 0;
}

void func_0020DD98(M2C_UNK *arg0, void *arg1) {
    u8 sp[512];
    s32 temp_16;
    s32 temp_17;

    temp_17 = func_00275340(M2C_FIELD(arg0, s32 *, 4));
    temp_16 = 0x100 - temp_17;
    func_00275398(sp, 0x100, M2C_FIELD(arg0, s32 *, 4));
    if (temp_16 > 0) {
        func_00275260(arg1, sp + (temp_17 * 2), temp_16);
    }
    func_0020DC60(arg0, temp_17 + temp_16);
    func_0020DE78(arg0, sp);
}
