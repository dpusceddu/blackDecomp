#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002707D8(void *, void *, s32, s32, s32, f32);

void func_002707A8(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0) {
    if (arg3 != 0) {
        func_002707D8(arg0, arg1, arg2, 1, arg4, fparg0);
        return;
    }
    func_002707D8(arg0, arg1, arg2, 0, arg4, fparg0);
}
