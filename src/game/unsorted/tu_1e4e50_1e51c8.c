#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001E5AF8();
extern s32 func_001E5DD0(void *);
extern s32 func_00138320();
extern s32 func_00135570();
extern s32 func_0012D158();
extern void * D_0040F4D0;
extern s32 func_001E4B70(s32);
extern M2C_UNK D_003BD478;

s32 func_001E51C8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x5C)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E51E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5360);

s32 func_001E5408(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + ((s32) &D_003BD478)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5830);

void func_001E5900(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x798) == 8) {
        func_001E5AF8();
        func_001E5DD0(arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5AF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5CB0);

s32 func_001E5CD8(void) {
    return 1;
}

s32 func_001E5CE0(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_18;

    var_16 = -1;
    var_18 = 0;
    temp_2 = func_00138320(func_00135570(arg1));
    if (temp_2 >= 0x24) {
        if (temp_2 < 0x26) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x594);
            var_16 = 2;
        } else if (temp_2 < 0x2B) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x590);
            var_16 = 1;
        }
    }
    return (func_0012D158(D_0040F4D0, 0, var_16 - 1) * 0x190) + var_18;
}

void func_001E5D80(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x170) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5F30);

s32 func_001E5FA8(s32 arg0) {
    return func_001E4B70(arg0 + 0x858) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5FC8);

void func_001E6050(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6058);

void func_001E6088(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x8AC) = (f32) M2C_FIELD(arg0, f32 *, 0x8C0);
    M2C_FIELD(arg0, f32 *, 0x8B0) = (f32) M2C_FIELD(arg0, f32 *, 0x8C4);
    M2C_FIELD(arg0, f32 *, 0x8B4) = (f32) M2C_FIELD(arg0, f32 *, 0x8C8);
    M2C_FIELD(arg0, s8 *, 0x8BC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E60A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E60E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6240);
