#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_001A6840(s32, M2C_UNK, M2C_UNK);
extern s32 func_00158088();
extern s32 func_00181F48(void *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1);

u8 func_0017FA58(void *arg0) {
    u8 var_5;
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    var_5 = 0;
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        var_5 = M2C_FIELD(temp_4, u8 *, 0x84A);
    }
    return var_5;
}

void func_0017FA78(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_3, u8 *, 0x3B) != 0) && (func_001A6840(M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s32 *, 0x330), 0, 1) != 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), u8 *, 0x3B) = 0U;
    }
}

void func_0017FAC8(void *arg0) {
    void *temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_3, u8 *, 0x31) == 0) && (func_00158088(M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s32 *, 0x2A4)) == 0)) {
        if (M2C_FIELD(arg0, u8 *, 0x82) != 0) {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s8 *, 0x33) = 1;
            M2C_FIELD(arg0, u8 *, 0x82) = 0U;
            temp_3_2 = M2C_FIELD(arg0, void **, 0x44);
            if (M2C_FIELD(temp_3_2, s32 *, 0x80) == 1) {
                func_00181F48(temp_3_2 + 0xC80, 0, 0xB, 0.0f, 2.0f);
            }
        } else {
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s8 *, 0x33) = 0;
        }
    }
}

void func_0017FB68(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x7C) = 0;
}

s32 func_0017FB70(void) {
    return 0;
}
