#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0014B8A0(s32 *);

s32 func_0014AC60(s32 *arg0) {
    func_0014B8A0(arg0);
    M2C_FIELD(arg0, s8 *, 0x118) = 0;
    M2C_FIELD(arg0, s32 *, 0xC4) = 5;
    M2C_FIELD(arg0, s8 *, 0x117) = 0;
    return 5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014AC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014ADF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B4D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B8A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014B948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BA78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BA80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BAA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014BCA0);
