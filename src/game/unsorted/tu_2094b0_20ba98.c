#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0035D728(void *, s8 *, ...);
extern s32 func_0021A218(s8 *, s8 *);
extern s8 D_0040DDF0;
extern s8 D_0040DDF8;

void func_0020BA98(void *arg0, s32 arg1, s32 arg2) {
    u8 sp[24] __attribute__((aligned(16)));
    func_0035D728(sp, "%s._visible\0\0\0\0\0_visible", arg0 + ((arg1 * 0xA) + 0x38BF));
    if (arg2 != 0) {
        func_0021A218(sp, &D_0040DDF0);
        return;
    }
    func_0021A218(sp, &D_0040DDF8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20ba98", func_0020BB00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20ba98", func_0020BB08);
