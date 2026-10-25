#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00364E20();
extern void * D_003D6944;

void func_00364E38(void) {
    func_00364E20(D_003D6944);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/libc/tu_360c10_364e38", func_00364E60);
