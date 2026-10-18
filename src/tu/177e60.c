#include "auto/prelude.h"

extern s32 func_00173640(void *, f32);

void func_00177E60(s128 *arg0, s128 arg1) {
    *arg0 = arg1;
}

void func_00177E68(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x60) = arg1;
}

void func_00177E70(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    func_00173640(arg0 + 0x5C, 5.0f);
}
