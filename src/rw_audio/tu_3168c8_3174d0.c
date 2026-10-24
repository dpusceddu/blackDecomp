#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00319CA8();
extern s32 D_0040E1A8;

s32 func_003174D0(void) {
    s32 temp_v0;

    temp_v0 = func_00319CA8();
    D_0040E1A8 = 0;
    return temp_v0;
}
