#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001EFBA0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5828);

s32 func_001D59C8(void) {
    func_001EFBA0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D59E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5C28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5C30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5CD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5828", func_001D5DA8);

#include "ps2/recovered_types.h"
extern void * D_003BD284;
extern void * D_003BD280;

s32 func_001D5E10(s32 arg0) {
    s32 temp_2;
    u32 temp_4;

    temp_2 = (s32) (D_003BD284 + 0xF) & ~0xF;
    temp_4 = temp_2 + arg0;
    D_003BD284 = (void *) temp_4;
    return ((u32) D_003BD280 < temp_4) ? 0 : temp_2;
}
