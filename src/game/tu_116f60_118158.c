#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern f32 func_001181C0(void *, s32);

f32 func_00118158(void *arg0, f32 fparg0) {
    return func_001181C0(arg0, M2C_FIELD(arg0, s32 *, 0x10)) - M2C_FIELD(arg0, f32 *, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00118188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001181C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00118210);
