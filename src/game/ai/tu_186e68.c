#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00187018();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00186E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00186F40);

void func_00186FF0(s32 *arg0) {
    if (*arg0 < 0x14) {
        func_00187018();
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001870C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001871E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187960);

void func_00187B10(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x4B0) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187C00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00187C68);
