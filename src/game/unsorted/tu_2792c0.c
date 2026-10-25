#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002797A0();
extern s32 func_00279390();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_002792C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279390);

#include "ps2/recovered_types.h"
extern s128 func_002688E0(f32, f32, f32);
extern u8 func_00268A50(s32);
extern u8 func_00268A78(s32);
extern u8 func_00268AA0(s32);

s32 func_00279700(void *arg0, s32 arg1) {
    f32 var_f12;

    var_f12 = (f32) M2C_FIELD(arg0, s32 *, 0x40) + 1.0f;
    if (arg1 != 0) {
        var_f12 += 0.2f;
    }
    func_002688E0(var_f12, 0.1f, 100.0f);
    func_00268A50(M2C_FIELD(arg0, s32 *, 0x44) > 0);
    func_00268A78(arg1);
    return func_00268AA0(arg1 ^ 1);
}

void func_00279790(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_002797A0);

s32 func_002798B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 0x44) < 0) {
        func_002797A0(arg0);
    }
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + 1);
    func_00279700(arg0, 1);
    func_00279390(arg0, arg1, arg2);
    temp_2 = M2C_FIELD(arg0, s32 *, 0x44) + 1;
    M2C_FIELD(arg0, s32 *, 0x44) = temp_2;
    return temp_2;
}

void func_00279930(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) - 1);
}

s32 func_00279940(s32 arg0, s32 arg1, s32 arg2) {
    func_00279700(arg0, 0);
    return func_00279390(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_00279E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0", func_0027A738);
