#include "auto/prelude.h"

void func_0023DD28(void *arg0, s32 arg1) {
    s16 temp_5;
    void *temp_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 4);
    temp_5 = M2C_FIELD(temp_3, s16 *, 0x20);
    temp_2 = M2C_FIELD(temp_3, void *(**)(void *, s16), 0x24)(arg0 + temp_5, temp_5);
    M2C_FIELD(temp_2, s32 *, 0x10) = (s32) (M2C_FIELD(temp_2, s32 *, 0x10) | arg1);
}

void func_0023DD68(void *arg0, s32 arg1) {
    s16 temp_5;
    void *temp_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 4);
    temp_5 = M2C_FIELD(temp_3, s16 *, 0x20);
    temp_2 = M2C_FIELD(temp_3, void *(**)(void *, s16), 0x24)(arg0 + temp_5, temp_5);
    M2C_FIELD(temp_2, s32 *, 0x10) = (s32) (M2C_FIELD(temp_2, s32 *, 0x10) & ~arg1);
}
