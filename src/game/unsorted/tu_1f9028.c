#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();
extern void func_00200A68(void *arg0);
extern s32 func_001F9028(void *);
extern s32 func_001FA468(void *);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F92A0);

void func_001F9980(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xB90) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9DE8);

void func_001F9EB0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    func_00200A68(arg0 + 0x20);
    func_001F9028(arg0 + 0xC0);
    func_001FA468(arg0 + 0xC80);
    M2C_FIELD(arg0, s32 *, 0xEA8) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F9EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA3A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA4D8);

s32 func_001FAB98(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FABA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FABD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FAC00);
