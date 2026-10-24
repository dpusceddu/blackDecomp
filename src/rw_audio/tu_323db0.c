#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_00458A60;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00323DB0);

void func_00323E20(void) {
    func_00311CA0(&D_00458A60);
}
