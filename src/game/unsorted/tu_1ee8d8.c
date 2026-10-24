#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00280B10();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EE8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EEB00);

s32 func_001EED58(void *arg0) {
    func_00280B10();
    M2C_FIELD(arg0, s8 *, 0x291) = 0;
    M2C_FIELD(arg0, s32 *, 0x250) = 2;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EED90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EED98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EF0C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EF258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EF260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EF360);
