#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0048AA70;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373A08);

void func_00373A78(void) {
    func_00311CA0(&D_0048AA70);
}
