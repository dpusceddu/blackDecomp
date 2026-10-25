#include "include_asm.h"

#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_00109F68(void *arg0, s32 arg1) {
    switch (arg1) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 17:
        return 0;
    case 13:
    case 14:
    case 15:
    case 16:
        return 1;
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_109308_109f68", func_00109FA8);
