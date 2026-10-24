#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003D71F4;
extern s32 * func_0035C6EC(s32 *, s32, s32);
extern s32 D_00486CA8;

s32 func_0036BCE8(void) {
    D_003D71F4 = 0;
    func_0035C6EC(&D_00486CA8, 0, 4);
    return 0;
}
