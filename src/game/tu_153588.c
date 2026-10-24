#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001535B0(void *, f32);
extern void * D_0040F4D0;

s32 func_00153588(void *arg0) {
    return func_001535B0(arg0, M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001535B0);
