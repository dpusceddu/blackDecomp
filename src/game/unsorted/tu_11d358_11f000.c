#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001735E0();
extern s32 func_00173610();
extern s32 func_0011F808();

s32 func_0011F000(s32 arg0) {
    s32 temp_17;
    s32 var_2;

    temp_17 = arg0 + 0x50;
    var_2 = func_001735E0(temp_17);
    if (var_2 != 0) {
        var_2 = (s32) M2C_FIELD(arg0, u8 *, 0x58);
        if (var_2 != 0) {
            var_2 = func_00173610(temp_17);
            if (var_2 != 0) {
                M2C_FIELD(arg0, u8 *, 0x58) = 0U;
                M2C_FIELD(arg0, s8 *, 0x5A) = 0;
                var_2 = func_0011F808(arg0);
            }
        }
    }
    return var_2;
}

s32 func_0011F068(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0011F070);
