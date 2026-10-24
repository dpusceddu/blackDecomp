#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0011D490();
extern s32 func_0011D430();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00120068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001204B0);

void func_001207B8(void) {
    func_0011D490();
}

s32 func_001207D8(s32 arg0) {
    return func_0011D430(arg0, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001207F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00120A48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00120AF0);

void func_00120CB0(void) {
    func_0011D490();
}

s32 func_00120CD0(s32 arg0) {
    return func_0011D430(arg0, 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00120CF0);

s32 func_00120EB8(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00120EC0);

void func_001215E0(void) {
    func_0011D490();
}
