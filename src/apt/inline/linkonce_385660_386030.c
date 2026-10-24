#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00387480();
extern M2C_UNK D_0040DE10;
extern u16 ** func_00387398();

void func_00386030(u16 **arg0, u16 **arg1) {
    f32 temp_f1;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_4;

    temp_3 = M2C_FIELD(arg1, s32 *, 0xC);
    if (temp_3 != 3) {
        M2C_FIELD(arg0, s32 *, 0xC) = temp_3;
    }
    temp_2 = M2C_FIELD(arg1, s32 *, 8);
    if (temp_2 != -1) {
        M2C_FIELD(arg0, s32 *, 8) = temp_2;
    }
    if (func_00387480(arg1, &D_0040DE10) != 0) {
        func_00387398(arg0, arg1);
    }
    temp_f1 = M2C_FIELD(arg1, f32 *, 4);
    if (temp_f1 != -1.0f) {
        M2C_FIELD(arg0, f32 *, 4) = temp_f1;
    }
    temp_3_2 = M2C_FIELD(arg1, s32 *, 0x10);
    if (temp_3_2 != 2) {
        M2C_FIELD(arg0, s32 *, 0x10) = temp_3_2;
    }
    temp_2_2 = M2C_FIELD(arg1, s32 *, 0x14);
    if (temp_2_2 != -1) {
        M2C_FIELD(arg0, s32 *, 0x14) = temp_2_2;
    }
    temp_2_3 = M2C_FIELD(arg1, s32 *, 0x18);
    if (temp_2_3 != -1) {
        M2C_FIELD(arg0, s32 *, 0x18) = temp_2_3;
    }
    temp_4 = M2C_FIELD(arg1, s32 *, 0x1C);
    if (temp_4 != -1) {
        M2C_FIELD(arg0, s32 *, 0x1C) = temp_4;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003860F8);
