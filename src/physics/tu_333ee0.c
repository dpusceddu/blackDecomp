#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00333EE0(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_333ee0", func_00333EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_333ee0", func_00334028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_333ee0", func_00334060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_333ee0", func_00334068);

void func_003340E0(void) {
    func_00333EE0(1, 0xFFFF);
}

void func_00334100(void) {
    func_00333EE0(0, 0xFFFF);
}
