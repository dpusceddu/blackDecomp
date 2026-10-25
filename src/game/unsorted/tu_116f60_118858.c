#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00118088();

s32 func_00118858(void *arg0, f32 *arg1) {
    func_00118088();
    *arg1 = M2C_FIELD(arg0, f32 *, 0x14);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_118858", func_00118898);
