#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0036B970();
extern void func_003678A0(); /* WaitSema */
extern s32 D_003D71FC;

s32 func_0036B9C8(s32 arg0) {
    func_0036B970();
    func_003678A0(D_003D71FC);
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036B9F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036BA08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036BA50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036BC58);
