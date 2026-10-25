#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193980();
extern s32 func_001A12E0(void *);
extern s32 func_00193990(void *, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a1100", func_001A1100);

void func_001A1250(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s32 *, 8) = -1;
    if (func_001A12E0(arg0) == 0) {
        func_00193990(arg0, 0);
    }
}
