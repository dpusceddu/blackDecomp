#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_0032A0E8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x444);
    return arg0;
}

s32 func_0032A0F8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x448);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_32a0e8", func_0032A108);
