#include "include_asm.h"
#include "ps2/prelude.h"

// Record payload address; the original payload class identity remains UNVERIFIED.
void *func_00383738(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), void **, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_383738", func_00383750);
