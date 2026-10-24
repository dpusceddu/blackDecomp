#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BD1DC;
extern s32 func_001C4628(M2C_UNK *);
extern M2C_UNK D_004173E0;
extern void * D_0040F4C0;
extern s32 func_001AE538();

s32 func_001C3E08(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C3E10);

void func_001C4130(s32 arg0) {
    D_003BD1DC = (arg0 != 0) ? 0 : 0x200;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C4148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C41D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C43F0);

void func_001C45C0(void) {
    func_001C4628(&D_004173E0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C45E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C4628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C49C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C49E0);

void func_001C4D00(void) {
    func_001C4F08(D_0040F4C0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C4D28);

void func_001C4F08(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, u32 *, 0xD5F0) = arg1;
    if (arg1 < (u32) M2C_FIELD(arg0, u32 *, 0xD5F4)) {
        M2C_FIELD(arg0, u32 *, 0xD5F4) = arg1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C4F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C4FB0);

void func_001C50E0(void) {
    func_001AE538();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C5100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C56F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C59F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C5B48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C5D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C5EB8);
