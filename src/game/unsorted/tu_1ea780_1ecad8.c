#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001ED4F0(s32);

void func_001ECAD8(s32 arg0) {
    func_001ED4F0(arg0 + 0x7B0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ECAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ECD50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ECEF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ECF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED068);
