#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002FB9D0(void *, void *, void *, s32, s32, f32);

s32 func_00305340(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    return func_002FB9D0(M2C_FIELD(arg0, void **, 0x64), arg1, M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x14), arg2 & 0xFF, arg3 & 0xFF, M2C_FIELD(arg0, f32 *, 0x38));
}
