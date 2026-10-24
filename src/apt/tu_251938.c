#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BFAD4;
extern s32 D_003BFAD8;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00251938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00251980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002519D0);

s32 func_00251A60(void) {
    s32 temp_2;
    s32 temp_3;

    temp_2 = D_003BFAD4;
    temp_3 = D_003BFAD8 * 4;
    D_003BFAD8 = 0;
    D_003BFAD4 = temp_2 + temp_3;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00251A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00251B38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00251D98);
