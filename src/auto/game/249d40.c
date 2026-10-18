#include "auto/prelude.h"

void func_00249D40(void *arg0) {
    s32 temp_2;
    void *temp_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x3B8);
    M2C_FIELD(arg0, s32 *, 0x3B8) = (s32) (temp_2 + 1);
    temp_3 = arg0 + ((temp_2 << 5) + 0x20);
    M2C_FIELD(temp_3, s128 *, 0) = (s128) M2C_FIELD(arg0, s128 *, 0);
    M2C_FIELD(temp_3, s128 *, 0x10) = (s128) M2C_FIELD(arg0, s128 *, 0x10);
}

void func_00249D70(void *arg0) {
    s32 temp_2;
    void *temp_5;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x3B8) - 1;
    M2C_FIELD(arg0, s32 *, 0x3B8) = temp_2;
    temp_5 = arg0 + ((temp_2 << 5) + 0x20);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
}
