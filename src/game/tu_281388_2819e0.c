#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00280EE0(void *, s32);

s32 func_002819E0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_4;
    u32 temp_17;

    var_16 = arg0;
    temp_17 = var_16 + 0xE00;
    var_4 = var_16;
    do {
        func_00280EE0((void *) var_4, arg1);
        var_16 += 0x38;
        temp_2 = (u32) var_16 < temp_17;
        var_4 = var_16;
    } while (temp_2 != 0);
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281C98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281D50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281E28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281EE0);
