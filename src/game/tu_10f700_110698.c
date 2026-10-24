#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001106B8(void *, u32, s32, f32, f32);

s32 func_00110698(void *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    return func_001106B8(arg0, (u32) arg1, arg2, fparg0, 0.0f);
}
