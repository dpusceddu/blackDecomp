#include "auto/prelude.h"

extern u8 D_003EFCC8;
extern s32 D_004548A4;
extern M2C_UNK D_003EF8C0;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_00305438;
extern u8 D_003EFD18;
extern s32 D_004548A8;
extern M2C_UNK D_003EFCD0;
extern M2C_UNK func_00305448;
extern u8 D_003EFD68;
extern s32 D_004548AC;
extern M2C_UNK D_003EFD20;
extern M2C_UNK func_00305460;
extern u8 D_003EFDB8;
extern s32 D_004548B0;
extern M2C_UNK D_003EFD70;
extern M2C_UNK func_00305478;
extern u8 D_003EFE08;
extern s32 D_004548B4;
extern M2C_UNK D_003EFDC0;
extern M2C_UNK func_00305490;

void func_003935A8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

s32 func_003935B0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

M2C_UNK * func_003935B8(M2C_UNK *arg0) {
    if (D_003EFCC8 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003EFCC8 = 0;
    return arg0;
}

M2C_UNK * func_003935D8(void) {
    if (D_004548A4 == 0) {
        func_003935B8(&D_003EF8C0);
        D_004548A4 = 1;
        func_0035E690(&func_00305438);
    }
    return &D_003EF8C0;
}

M2C_UNK * func_00393630(M2C_UNK *arg0) {
    if (D_003EFD18 != 0) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
    }
    D_003EFD18 = 0;
    return arg0;
}

M2C_UNK * func_00393650(void) {
    if (D_004548A8 == 0) {
        func_00393630(&D_003EFCD0);
        D_004548A8 = 1;
        func_0035E690(&func_00305448);
    }
    return &D_003EFCD0;
}

M2C_UNK * func_003936A8(M2C_UNK *arg0) {
    if (D_003EFD68 != 0) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
    }
    D_003EFD68 = 0;
    return arg0;
}

M2C_UNK * func_003936C8(void) {
    if (D_004548AC == 0) {
        func_003936A8(&D_003EFD20);
        D_004548AC = 1;
        func_0035E690(&func_00305460);
    }
    return &D_003EFD20;
}

M2C_UNK * func_00393720(M2C_UNK *arg0) {
    if (D_003EFDB8 != 0) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
    }
    D_003EFDB8 = 0;
    return arg0;
}

M2C_UNK * func_00393740(void) {
    if (D_004548B0 == 0) {
        func_00393720(&D_003EFD70);
        D_004548B0 = 1;
        func_0035E690(&func_00305478);
    }
    return &D_003EFD70;
}

M2C_UNK * func_00393798(M2C_UNK *arg0) {
    if (D_003EFE08 != 0) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
    }
    D_003EFE08 = 0;
    return arg0;
}

M2C_UNK * func_003937B8(void) {
    if (D_004548B4 == 0) {
        func_00393798(&D_003EFDC0);
        D_004548B4 = 1;
        func_0035E690(&func_00305490);
    }
    return &D_003EFDC0;
}
