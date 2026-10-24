#include "ps2/prelude.h"

extern s32 func_0018DDD8();
extern s32 func_0018AB08();
extern s32 func_00384290();
extern s32 func_0018D608();
extern s32 func_00188F10();
extern s32 func_00188F58();
extern s32 func_0018D658();
extern s32 func_00174B58(s32, s32);
extern s32 func_00174BA0(s32, s32);

void func_0018E2E8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

s32 func_0018E2F0(void *arg0) {
    if (func_0018DDD8(M2C_FIELD(arg0, s32 *, 4) + 0xC94) != 0) {
        M2C_FIELD(arg0, s32 *, 8) = 1;
    } else {
        M2C_FIELD(arg0, s32 *, 8) = 0;
    }
    return 1;
}

void func_0018E338(void *arg0) {
    void *temp_16;
    void *temp_16_2;
    void *temp_17;
    void *temp_3;
    void *temp_4;

    if (M2C_FIELD(arg0, u8 *, 0xC) == 0) {
        if (func_0018AB08(M2C_FIELD(arg0, s32 *, 4) + 0x150) != 0) {
            func_00384290(arg0);
        }
        if (M2C_FIELD(arg0, u8 *, 0xC) != 0) {
            goto block_4;
        }
    } else {
block_4:
        temp_4 = M2C_FIELD(arg0, s32 *, 4) + 0xD10;
        if ((M2C_FIELD(temp_4, u8 *, 0x16) != 0) && (func_0018D608(temp_4) == 0) && (func_00188F10(M2C_FIELD(arg0, s32 *, 4) + 0x150) != 0) && (func_0018AB08(M2C_FIELD(arg0, s32 *, 4) + 0x150) != 0)) {
            temp_16 = M2C_FIELD(arg0, void **, 0x10);
            temp_16_2 = temp_16 + 0x78;
            temp_17 = arg0 + M2C_FIELD(temp_16, s16 *, 0x78);
            if (M2C_FIELD(temp_16_2, s32 (**)(void *, s32), 4)(temp_17, func_00188F58(M2C_FIELD(arg0, s32 *, 4) + 0x150)) != 0) {
                temp_3 = M2C_FIELD(arg0, void **, 0x10);
                if (M2C_FIELD(temp_3, s32 (**)(void *), 0xAC)(arg0 + M2C_FIELD(temp_3, s16 *, 0xA8)) != 0) {
                    func_0018D658(M2C_FIELD(arg0, s32 *, 4) + 0xD10);
                }
            }
        }
    }
}

s32 func_0018E448(void) {
    return 1;
}

void func_0018E450(void) {

}

void func_0018E458(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    if (arg1 != 0) {
        func_00174B58(arg1, M2C_FIELD(arg0, s32 *, 4));
    }
}

void func_0018E488(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_4 != 0) {
        func_00174BA0(temp_4, M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
}
