#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0013C950(void *, s32);
extern M2C_UNK * D_0040F4D0;
extern s32 func_001F2838(s32, s32, s32);
extern s32 D_0040F51C;

s32 func_00121648(void) {
    func_0013C950((void *) (((s8 *) D_0040F4D0) + 0x30), 0);
    func_001F2838(D_0040F51C, 0, 1);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_121648", func_00121688);
