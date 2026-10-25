#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035E828(s32);

void func_00125588(void *arg0) {
    func_0035E828(M2C_FIELD(arg0, s32 *, 0x3BC));
    M2C_FIELD(arg0, s32 *, 0x3C0) = 0;
    M2C_FIELD(arg0, s32 *, 0x3BC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_125588", func_001255B8);
