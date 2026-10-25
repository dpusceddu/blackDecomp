#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001179B8();

s32 func_00117930(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    func_001179B8(arg0, arg1);
    M2C_FIELD(arg1, f32 *, 0) = 45.0f;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_117930", func_00117970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_117930", func_001179B8);
