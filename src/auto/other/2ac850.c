#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C3358;

s32 func_002AC850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C3358, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}
