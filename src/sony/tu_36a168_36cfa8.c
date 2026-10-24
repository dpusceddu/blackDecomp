#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_003D7210;
extern s32 func_0035C6EC();
extern s32 D_00487168;

s32 func_0036CFA8(void) {
    D_003D7210 = -1;
    func_0035C6EC(&D_00487168, 0, 4U);
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036CFE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036CFF0);
