#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018BE88();

s32 func_0018BEB0(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_0018BE88(arg0, 0x13);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BEE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BF28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BFA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018BFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_18be60_18beb0", func_0018C068);
