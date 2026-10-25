#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0035D1A0(s32, s8 *, s32);
extern s8 * D_003BCEAC;

void func_00144038(void *arg0, s8 *arg1) {
    if (arg1 == NULL) {
        func_0035D1A0((s32) (arg0 + 0x84), D_003BCEAC, 0x3F);
        return;
    }
    func_0035D1A0((s32) (arg0 + 0x84), arg1, 0x3F);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1435d0_144038", func_00144078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1435d0_144038", func_001440B8);
