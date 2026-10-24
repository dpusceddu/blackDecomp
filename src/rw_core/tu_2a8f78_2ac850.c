#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C3358;

s32 func_002AC850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C3358, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC898);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC8A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AC908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ACBE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ACE68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD1B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD2C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD4A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD5D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002AD660);
