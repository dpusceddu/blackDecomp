#include "ps2/prelude.h"

extern s32 func_00198568();
extern s32 func_00182410();
extern s128 * func_001893A0();
extern s32 func_00180B70();
extern s32 func_00193A60(void **, M2C_UNK, f32);

void func_00198B10(void **arg0) {
    void *temp_16;
    void *temp_16_2;

    func_00198568();
    temp_16 = *arg0;
    func_00182410(temp_16 + 0x810, *func_001893A0(temp_16 + 0x150), 0, 0);
    temp_16_2 = *arg0;
    if (func_00180B70(temp_16_2 + 0xB30, *func_001893A0(temp_16_2 + 0x150)) != 0) {
        func_00193A60(arg0, 0, 10.0f);
        return;
    }
    func_00193A60(arg0, 0, 0.5f);
}
