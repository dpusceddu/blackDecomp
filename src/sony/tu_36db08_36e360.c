#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0036D518();
extern s32 func_0036E2F0();
extern s32 func_0036D568();

s32 func_0036E360(void) {
    s32 temp_16;
    s32 temp_17;

    temp_16 = func_0036D518();
    temp_17 = func_0036E2F0();
    if (temp_16 != 0) {
        func_0036D568();
    }
    return temp_17;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E3A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E4B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E4E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E6D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E6E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036E8C0);
