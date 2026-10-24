#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001AB3E0(void *arg0, s32 arg1) {
    s32 *var_2;
    s32 var_3;

    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    if (M2C_FIELD(arg0, u8 *, 0x20) == 0) {
        var_3 = 7;
        var_2 = (s32 *) (((s8 *) arg0) + 0x1C);
        do {
            *var_2 = 0;
            var_3 -= 1;
            var_2 = (s32 *) (((s8 *) var_2) + -4);
        } while (var_3 >= 0);
        M2C_FIELD(arg0, u8 *, 0x20) = 1U;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AB428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AB468);
