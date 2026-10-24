#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00153190(void *arg0) {
    s32 var_5;
    s8 *temp_2;

    var_5 = 0;
    do {
        temp_2 = M2C_FIELD(arg0, s32 *, 4) + var_5;
        var_5 += 1;
        *temp_2 = 0;
    } while (var_5 < 0x64);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001531B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001531C0);
