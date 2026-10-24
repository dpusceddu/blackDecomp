#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00125B18(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00125B18);

void func_00125C38(void) {
    func_00125B18(1, 0xFFFF);
}

void func_00125C58(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xB0) = arg1;
}
