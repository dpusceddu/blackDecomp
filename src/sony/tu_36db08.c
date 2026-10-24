#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0036DB08();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DB08);

void func_0036DB78(s64 arg0) {
    func_0036DB08(0xB0001000, arg0);
}

void func_0036DB88(s64 arg0) {
    func_0036DB08(0xB0001010, arg0);
}

void func_0036DB98(s64 arg0) {
    func_0036DB08(0xB0001020, arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DBA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DD00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DD08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DDA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0036DF30);
