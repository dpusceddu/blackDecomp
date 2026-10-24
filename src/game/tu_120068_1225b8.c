#include "ps2/prelude.h"

void func_001225B8(void **arg0, s32 arg1) {
    void *temp_3;
    void *temp_3_2;
    void *temp_3_3;
    void *temp_3_4;
    void *temp_3_5;

    if (arg1 & 4) {
        temp_3 = *arg0;
        M2C_FIELD(temp_3, u8 *, 0x17) = (u8) (M2C_FIELD(temp_3, u8 *, 0x17) + 1);
        return;
    }
    if (arg1 & 8) {
        temp_3_2 = *arg0;
        M2C_FIELD(temp_3_2, u8 *, 0x18) = (u8) (M2C_FIELD(temp_3_2, u8 *, 0x18) + 1);
        return;
    }
    if (arg1 & 0x10) {
        temp_3_3 = *arg0;
        M2C_FIELD(temp_3_3, u8 *, 0x19) = (u8) (M2C_FIELD(temp_3_3, u8 *, 0x19) + 1);
        return;
    }
    if (arg1 & 2) {
        temp_3_4 = *arg0;
        M2C_FIELD(temp_3_4, u8 *, 0x16) = (u8) (M2C_FIELD(temp_3_4, u8 *, 0x16) + 1);
        return;
    }
    temp_3_5 = *arg0;
    if (arg1 & 0x20) {
        M2C_FIELD(temp_3_5, u8 *, 0x1A) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x1A) + 1);
        return;
    }
    M2C_FIELD(temp_3_5, u8 *, 0x15) = (u8) (M2C_FIELD(temp_3_5, u8 *, 0x15) + 1);
}
