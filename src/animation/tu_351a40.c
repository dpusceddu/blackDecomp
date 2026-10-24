#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00351A40);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00107D48(s32, s32);

s32 * func_00351A78(s32 arg0, s32 arg1) {
    s32 temp_6;
    s32 var_2;
    s32 var_3;

    temp_6 = arg0 + 4;
    if (temp_6 != 0) {
        var_3 = arg0 + 0x84;
        var_2 = arg1 & 1;
        if (temp_6 != var_3) {
            do {
                var_3 -= 8;
            } while (temp_6 != var_3);
            goto block_3;
        }
    } else {
block_3:
        var_2 = arg1 & 1;
    }
    if (var_2 != 0) {
        var_2 = func_00107D48(arg0, arg1);
    }
    return (s32 *) var_2;
}
