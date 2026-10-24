#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002454D0);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern u16 D_0040DE46;
extern s32 func_002454D0(s32);

s32 func_002455C0(s32 arg0) {
    D_0040DE46 += 1;
    return func_002454D0(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002455E8);
