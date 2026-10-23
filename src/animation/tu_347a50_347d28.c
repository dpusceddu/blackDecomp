#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00347CA0(s32 *, s8 *, s32, f32);

s32 func_00347D28(s32 *arg0, s8 *arg1) {
    return func_00347CA0(arg0, arg1, 0, 0.0f);
}
