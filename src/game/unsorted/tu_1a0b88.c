#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_001A0C18(void *);

void func_001A0B88(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s32 *, 8) = 2;
    func_001A0C18(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0b88", func_001A0BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0b88", func_001A0C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0b88", func_001A0D48);
