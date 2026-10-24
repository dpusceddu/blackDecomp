#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204910(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00204910);

void func_00204A30(void) {
    func_00204910(1, 0xFFFF);
}
