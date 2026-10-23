#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00294840(void *, s32, s32);
extern s32 func_002946D0(void *, s32, s32);

s32 func_00294CE8(void *arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0x184) != 3) {
        return func_00294840(arg0, arg1, arg2);
    }
    return func_002946D0(arg0, arg1, arg2);
}
