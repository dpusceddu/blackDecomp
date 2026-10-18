#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_003BD284;
extern void * D_003BD280;

s32 func_001D5E10(s32 arg0) {
    s32 temp_2;
    u32 temp_4;

    temp_2 = (s32) (D_003BD284 + 0xF) & ~0xF;
    temp_4 = temp_2 + arg0;
    D_003BD284 = (void *) temp_4;
    return ((u32) D_003BD280 < temp_4) ? 0 : temp_2;
}
