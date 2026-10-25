#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016DD68);

s32 func_0016DDB0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x22BBC) != 0;
}

s32 func_0016DDC8(s32 arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x22BBC);
    M2C_FIELD(arg0, void **, 0x22BBC) = (void *) M2C_FIELD(temp_2, void **, 0x1EF0);
    return (s32) temp_2;
}

void func_0016DDE0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1EF0) = (void *) M2C_FIELD(arg0, void **, 0x22BBC);
    M2C_FIELD(arg0, void **, 0x22BBC) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016DDF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016DE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016DEF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016DFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E0C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E1F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E250);

#include "ps2/recovered_types.h"
extern s8 * func_00172C88(void *, s128, s128);
extern s8 * func_0016E588(void *, s128);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0016E2B8(void *arg0, s128 arg1, s128 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s8 *var_2;

    if (arg3 != 0) {
        return func_00172C88(arg0 + 0x22800, arg1, arg2);
    }
    var_2 = func_0016E588(arg0, arg2);
    if (var_2 != NULL) {
        var_2 = func_00181F48(var_2 + 0xC80, 0, 0x11, 0.0f, 1.0f);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E3C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E588);
