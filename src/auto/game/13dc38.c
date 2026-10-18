#include "auto/prelude.h"

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
