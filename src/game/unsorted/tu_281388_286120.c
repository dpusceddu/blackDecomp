#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 func_0029DC18(f32);
extern f32 func_0029DA28(f32);
extern s32 func_00286220(s32, s32, s32, f32, f32, f32, f32, f32, f32);

s32 func_00286120(s32 arg0) {
    return func_00286140(arg0, arg0, arg0 + 0x70);
}

void func_00286140(s32 arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;

    temp_f20 = (fparg0 * 6.2831855f) / 48000.0f;
    temp_f22 = func_0029DC18(temp_f20);
    temp_f0 = func_0029DA28(temp_f20);
    temp_f13 = 1.0f - temp_f0;
    temp_f22_2 = temp_f22 / (2.0f * fparg1);
    temp_f12 = temp_f13 * 0.5f;
    func_00286220(arg0, arg1, arg2, temp_f12, temp_f13, temp_f12, temp_f22_2 + 1.0f, temp_f0 * -2.0f, 1.0f - temp_f22_2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286120", func_00286210);
