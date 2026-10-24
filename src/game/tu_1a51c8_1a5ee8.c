#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001A7450();
extern s32 func_001A6E58();

s32 func_001A5EE8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x54) != 0) {
        func_001A7450();
        if (M2C_FIELD(arg0, s32 *, 0x58) != 0) {
            func_001A6E58(arg0);
        }
    }
    M2C_FIELD(arg0, s8 *, 0xB8) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A5F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A61D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A6330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A67B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A67B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A6840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A68B0);
