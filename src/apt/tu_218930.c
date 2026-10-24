#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0021A130();
extern s32 D_0043DF50;
extern void * D_0043DF68;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218BA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218C20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218C30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00218EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00219EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A190);

void func_0021A1F0(void) {
    func_0021A130();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021A7E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021AA70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021AA98);

void func_0021AD58(void) {
    if ((D_0043DF50 == 0) && (D_0043DF68 != NULL)) {
        M2C_FIELD(D_0043DF68, s32 *, 0x24) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021AD80);
