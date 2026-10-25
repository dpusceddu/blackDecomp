#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003486E0();
extern s32 func_00352A30();

s32 func_003485E8(u32 *arg0, u32 *arg1) {
    u32 temp_3;
    u32 temp_4;

    temp_4 = *arg0;
    temp_3 = *arg1;
    if (temp_3 >= temp_4) {
        return (temp_4 >= temp_3) ? 0 : -1;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3485e8", func_00348610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3485e8", func_003486E0);

void func_00348738(s32 arg0, s32 arg1, s32 arg2) {
    func_003486E0(func_00352A30(), arg1, arg2);
}
