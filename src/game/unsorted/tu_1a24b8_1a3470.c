#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001A24B8();

s32 func_001A3470(void) {
    return 1;
}

s32 func_001A3478(void) {
    func_001A24B8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A3498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A3590);
