#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00281620(void *, f32, f32, f32, f32, f32);
extern s32 func_002805A0(void *, f32);

void func_002807B0(s32 arg0, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4) {
    func_00281620(arg0 + 0xB308, fparg0, fparg1, fparg2, fparg3, fparg4);
    func_002805A0(arg0 + 0xCB7C, fparg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0_2807b0", func_002807F8);
