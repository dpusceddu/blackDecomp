#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001092F8();
extern s32 func_00288930(s32);
extern s32 func_00108540(s32, M2C_UNK, s32, s16);
extern s32 D_0040F4C4;
extern s16 func_0012D508(void *arg0);
extern void * D_0040F4D0;

void func_0012A480(void) {
    s32 temp_2;

    temp_2 = func_001092F8();
    func_00288930(temp_2);
    func_00108540(D_0040F4C4, 0xC, temp_2, func_0012D508(D_0040F4D0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A4D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A5F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012A918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012AE58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B0E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012B950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012BB60);
