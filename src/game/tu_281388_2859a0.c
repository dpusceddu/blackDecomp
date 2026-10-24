#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_0040EBB8;
extern u8 D_0040EBBC;
extern s32 D_0040EBB4;

s32 func_002859A0(void) {
    D_0040EBB8 = 0;
    D_0040EBBC = 0;
    return D_0040EBB4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002859B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002859D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002859F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002859F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00285A98);
