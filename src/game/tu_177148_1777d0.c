#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001777D0(void *arg0) {
    s32 var_3;
    void *var_2;

    var_3 = 0x12B;
    var_2 = arg0;
    do {
        M2C_FIELD(var_2, s32 *, 0) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, s32 *, 4) = 0;
        var_2 = (void *) (((s8 *) var_2) + 8);
    } while (var_3 >= 0);
    M2C_FIELD(arg0, s32 *, 0x968) = 0;
    M2C_FIELD(arg0, s32 *, 0x960) = 0;
    M2C_FIELD(arg0, s32 *, 0x964) = 0;
    return (s32) var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001778A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001779C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001779D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001779E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001779E8);
