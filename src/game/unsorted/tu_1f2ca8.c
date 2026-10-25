#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001F8FF8(void *arg0, s8 arg1);
extern void * D_0040F518;
extern s32 func_001F8528(s32, s32);

void func_001F2CA8(s32 arg0, s8 *arg1) {
    func_001F8FF8(M2C_FIELD(D_0040F518, void **, 0x38), *arg1);
}

void func_001F2CD0(s32 arg0, s32 arg1) {
    func_001F8528(M2C_FIELD(D_0040F518, s32 *, 0x34), arg1 ^ 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f2ca8", func_001F2CF8);
