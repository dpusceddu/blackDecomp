#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * D_0040E25C;
extern u32 D_0040E260;

void func_00324E38(s32 *arg0, u32 arg1) {
    D_0040E25C = arg0;
    D_0040E260 = arg1;
}
