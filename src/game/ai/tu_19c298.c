#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_00188148(void *, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c298", func_0019C298);

void func_0019C2F8(s32 *arg0) {
    func_00193988();
    func_00188148(*arg0 + 0x290, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_19c298", func_0019C330);
