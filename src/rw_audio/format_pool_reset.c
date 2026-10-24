#include "include_asm.h"

#include "rw_audio/sound.h"

extern void func_00317FC0(void *);
extern u8 D_004563D0[];
extern u32 D_0040E198;

void func_00316598(void) {
    func_00317FC0(D_004563D0);
    D_0040E198=0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003165C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003165C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316668);
