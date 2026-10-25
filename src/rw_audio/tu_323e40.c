#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_00458A88;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323e40", func_00323E40);

void func_00323EB0(void) {
    func_00311CA0(&D_00458A88);
}
