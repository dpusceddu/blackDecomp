#include "auto/prelude.h"

extern s32 func_003486E0(s32 arg0, s32 arg1, s32);
extern s32 func_00348738(s32 arg1, s32 arg2, s32);
extern s32 D_003D2520;

void func_003483A0(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = (M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1C);
    func_003486E0(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
}

s32 func_003483E0(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_3;

    if (arg0 != NULL) {
        temp_3 = M2C_FIELD(arg0, void **, 4);
        if (temp_3 != NULL) {
            temp_2 = (M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(temp_3, s32 *, 0x1C);
            return func_003486E0(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}

void func_00348430(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = (M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1C);
    func_00348738(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
}

s32 func_00348470(void *arg0, s32 arg1) {
    void *temp_2;
    void *temp_3;

    if (arg0 != NULL) {
        temp_3 = M2C_FIELD(arg0, void **, 4);
        if (temp_3 != NULL) {
            temp_2 = (M2C_FIELD(arg0, s16 *, 8) * 0x10) + M2C_FIELD(temp_3, s32 *, 0x1C);
            return func_00348738(arg1, M2C_FIELD(temp_2, s32 *, 0xC), M2C_FIELD(temp_2, s32 *, 0));
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return -1;
    }
    return -1;
}

void func_003484C0(s32 arg0) {
    D_003D2520 = arg0;
}
