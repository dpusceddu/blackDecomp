#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00285880();
extern s32 func_00313FD0();
extern s32 func_003110B0(s32, M2C_UNK, M2C_UNK);
extern s32 func_002803F8();
extern s32 func_00280528();
extern s32 func_003178B8(M2C_UNK);
extern s32 func_00280628();

void func_00282880(void) {

}

s32 func_00282888(void) {
    func_00282AD8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_002828A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282A40);

void func_00282AD8(void *arg0) {
    u32 var_18;
    void *var_16;

    if (M2C_FIELD(arg0, s32 *, 0x1038) != 0) {
        var_18 = 0;
        if (M2C_FIELD(arg0, u32 *, 0x1028) != 0) {
            var_16 = arg0 + 0x10;
            do {
                var_18 += 1;
                func_00285880(var_16);
                var_16 += 0x20;
            } while (var_18 < (u32) M2C_FIELD(arg0, u32 *, 0x1028));
        }
        func_00313FD0(M2C_FIELD(arg0, s32 *, 0x1038));
        M2C_FIELD(arg0, s32 *, 0x1038) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x102E) = 0;
    M2C_FIELD(arg0, s32 *, 0x103C) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282BA0);

void func_00282C18(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x70);
    if (temp_4 != 0) {
        func_003110B0(temp_4, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x70) = 0;
    }
    func_002803F8(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282E70);

s32 func_00282EF8(void *arg0) {
    func_00280528();
    if (M2C_FIELD(arg0, s32 *, 8) == 1) {
        func_003178B8(2);
    } else {
        func_003178B8(3);
    }
    return 1;
}

void func_00282F48(void *arg0) {
    func_00280628();
    func_003110B0(M2C_FIELD(arg0, s32 *, 0x14), 0, 0);
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00282FD0);

void func_002830E8(void *arg0, f32 fparg0) {
    void *temp_3;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), f32 *, 0x80) = fparg0;
    temp_3 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_3, s32 *, 0x88) = (s32) (M2C_FIELD(temp_3, s32 *, 0x88) | 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00283108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_282880", func_00283198);
