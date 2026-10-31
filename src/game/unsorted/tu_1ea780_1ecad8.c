#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001ED4F0(s32);

void func_001ECAD8(s32 arg0) {
    func_001ED4F0(arg0 + 0x7B0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ECAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ECD50);


s32 func_001ECEF8(void* arg0, s32 arg1, s32 arg2) {
    s32 var_3;

    switch (arg1) {
        case 4:
        case 5: var_3 = 0xB; break;
        case 1:
        case 3: var_3 = (arg2 != 0) ? 4 : 7; break;
        case 2: var_3 = (arg2 != 0) ? 5 : 8; break;
        case 7: var_3 = 0xA; break;
        case 8: var_3 = 0xC; break;
        case 9: var_3 = 6; break;
        case 10: var_3 = 9; break;
        case 11: var_3 = 3; break;
        case 12: var_3 = 2; break;
        case 0:
        case 13:
        default: var_3 = 0xE; break;
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ECF80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ecad8", func_001ED068);
