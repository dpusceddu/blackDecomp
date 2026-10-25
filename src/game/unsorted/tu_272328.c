#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 D_003C95A8;
extern s32 func_002E91C0();
extern s32 func_002E9630(void *, s32);

void func_00272328(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x46) = 0;
}

f32 func_00272330(void) {
    return D_003C95A8;
}

void func_00272340(f32 fparg0) {
    func_002E91C0();
    D_003C95A8 += fparg0;
}

void func_00272378(s32 arg0) {
    func_002E9630(func_002E91C0(), arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_272328", func_002723A8);
