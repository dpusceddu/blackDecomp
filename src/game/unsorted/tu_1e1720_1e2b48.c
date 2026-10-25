#include "include_asm.h"

#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00280100(s32, void *);
extern void * D_0040F510;
extern s32 func_00280B10(void *);

s32 func_001E2B48(void *arg0) {
    s32 temp_2;
    void *temp_5;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x244);
    switch (temp_2) {
    case 2:
    case 3:
        M2C_FIELD(arg0, s32 *, 0x244) = 5;
        /* fallthrough */
    case 5:
        temp_5 = M2C_FIELD(arg0, void **, 0x24C);
        if (temp_5 != NULL) {
            if (func_00280100((s32) D_0040F510, temp_5) != 0) {
                M2C_FIELD(arg0, void **, 0x24C) = NULL;
                goto block_6;
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
block_6:
        M2C_FIELD(arg0, s32 *, 0x244) = 4;
    case 4:
        if (func_00280B10(arg0) != 0) {
            M2C_FIELD(arg0, s32 *, 0x244) = 6;
        case 1:
        case 6:
            return 1;
        }
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720_1e2b48", func_001E2BE8);
