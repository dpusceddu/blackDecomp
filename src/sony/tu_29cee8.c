#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s8 D_003C15F8;
extern s32 func_0029CEE8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029CEE8);

s32 func_0029CF58(void) {
    if (M2C_FIELD(&D_003C15F8, s8 *, 0) == 0) {
        func_0029CEE8();
    }
    return M2C_FIELD(&D_003C15F8, s8 *, 4) == 0x54;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029CF98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029CFF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D0A0);
