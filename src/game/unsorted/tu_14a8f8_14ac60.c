#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0014B8A0(s32 *);

s32 func_0014AC60(s32 *arg0) {
    func_0014B8A0(arg0);
    M2C_FIELD(arg0, s8 *, 0x118) = 0;
    M2C_FIELD(arg0, s32 *, 0xC4) = 5;
    M2C_FIELD(arg0, s8 *, 0x117) = 0;
    return 5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_14a8f8_14ac60", func_0014BCA0);
