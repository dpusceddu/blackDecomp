#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_003822E0(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 8);
}

s32 func_003822F8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 8);
}

s32 func_00382310(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_3822e0", func_00382328);
