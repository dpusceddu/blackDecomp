#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002CEA78();

s32 func_002CE980(s32 arg0) {
    func_002CEA78();
    return arg0;
}

s32 func_002CE9A8(void) {
    return 1;
}

void func_002CE9B0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2ce980", func_002CE9B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2ce980", func_002CEA70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce950_2ce980", func_002CEA78);
