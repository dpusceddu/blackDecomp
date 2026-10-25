#include "include_asm.h"
#include "ps2/prelude.h"

void func_0017E5A8(void *arg0, s128 arg1, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x74) = fparg0;
    M2C_FIELD(arg0, s128 *, 0x30) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_17c908_17e5a8", func_0017E5B8);
