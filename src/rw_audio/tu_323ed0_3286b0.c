#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0045C098;

void func_003286B0(void) {
    func_00311CA0(&D_0045C098);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003286D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003287F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328968);
