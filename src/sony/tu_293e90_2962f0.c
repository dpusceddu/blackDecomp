#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0036A038();
extern s32 func_00369FF0();
extern void func_00296468();
extern s32 func_00298CF0();

void func_002962F0(M2C_UNK *arg0) {
    func_0036A038("[MPEG ERROR]%s\n", arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002963A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296468);

void func_002964C0(M2C_UNK *arg0, s32 arg1, s32 arg2) {
    u8 sp[248] __attribute__((aligned(16)));
    func_00369FF0(sp, 0x100, arg1, arg2);
    func_00296468(arg0, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00296FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297468);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002978C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00297BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002981C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298890);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002989F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298CF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00298D88);

void func_00298DC0(void) {
    func_00298CF0();
}
