#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F2A38();
extern s32 D_0040F51C;
extern s32 func_00108818();
extern s32 D_0040F4C4;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015D958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015EF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_0015FDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_001603A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_001604A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160AA8);

void func_00160B30(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_00160B48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160B58);

void func_00160B60(s64 **arg0, s32 arg1) {
    if ((u32) (M2C_FIELD(arg0, s32 *, 8) - 1) >= 3U) {
        M2C_FIELD(arg0, s32 *, 8) = 1;
        if (arg1 != 0) {
            func_001F2A38(D_0040F51C, func_00108818(D_0040F4C4, M2C_FIELD(M2C_FIELD(arg0, s64 **, 0), s32 *, 0x10)), arg0);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958", func_00160E10);
