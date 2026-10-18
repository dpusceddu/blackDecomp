#include "auto/prelude.h"

extern s32 func_00343FC8();
extern s32 func_00344008();

void * func_0034F360(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_UNK *temp_17;
    M2C_UNK *temp_18;
    M2C_UNK *temp_19;
    M2C_UNK *temp_20;
    M2C_UNK *temp_21;

    temp_17 = arg0 + 0x30;
    temp_18 = arg0 + 0x50;
    temp_19 = arg0 + 0x70;
    temp_20 = arg0 + 0x90;
    temp_21 = arg0 + 0x10;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (arg3 - 1);
    func_00343FC8(temp_21);
    func_00343FC8(temp_17);
    func_00343FC8(temp_18);
    func_00343FC8(temp_19);
    func_00343FC8(temp_20);
    func_00344008(temp_21);
    func_00344008(temp_17);
    func_00344008(temp_18);
    func_00344008(temp_19);
    func_00344008(temp_20);
    return arg0;
}

void * func_0034F420(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    return arg0;
}
