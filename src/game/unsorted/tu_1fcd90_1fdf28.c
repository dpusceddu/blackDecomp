#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern s32 func_00275260();
extern M2C_UNK D_0040DDA8;

void func_001FDF28(void) {
    func_001FDFF8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FDF48);

void func_001FDFF8(void) {

}

void func_001FE000(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x154) = 0;
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    func_00275260(&D_0040DDA8, arg0 + 0x24, 0x40);
    func_00275260(&D_0040DDA8, arg0 + 0xA4, 0x40);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FE068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FE380);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FFDC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FFE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FFF88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_001FFF90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_00200080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_00200088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_00200678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_002006F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1fcd90_1fdf28", func_00200858);
