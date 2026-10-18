#include "auto/prelude.h"

extern s32 func_00162420();
extern void * func_00135550();
extern s32 func_0013D8B8();
extern s32 func_001791D8();
extern void * D_0040F4D4;

void func_001622D0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1C) != 0) {
        func_00162310();
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x1C) = 1U;
    func_00162420(arg0);
}

void func_00162310(void *arg0) {
    s32 temp_5;
    s64 *temp_4;

    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    temp_4 = M2C_FIELD(arg0, s64 **, 0x20);
    if ((temp_4 != NULL) && (M2C_FIELD(temp_4, s32 *, 0x37C) == M2C_FIELD(arg0, s32 *, 0x2C)) && (func_00135550(temp_4) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), s32 *, 0x80) == 1)) {
        func_0013D8B8(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), arg0);
    }
    temp_5 = M2C_FIELD(arg0, s32 *, 0x30);
    if (temp_5 != -1) {
        func_001791D8(D_0040F4D4 + 0xFA8, temp_5);
        M2C_FIELD(arg0, s32 *, 0x30) = -1;
    }
    M2C_FIELD(arg0, s64 **, 0x20) = NULL;
}
