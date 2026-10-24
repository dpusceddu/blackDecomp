#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001BE890();

s32 func_001BE2F0(void) {
    func_001BE890();
    return 1;
}

s32 func_001BE310(void) {
    func_001BE890();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE890);
