#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00176460(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0x2A;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    return 0x2A;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00176488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001764E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00176628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001766D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00176728);
