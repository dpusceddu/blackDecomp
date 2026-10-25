#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00160ED8();

s32 func_00162938(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_162938", func_00162958);
