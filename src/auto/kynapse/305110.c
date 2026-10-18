#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002E27F8(void *, void *, s32, s32, f32);

s32 func_00305110(void *arg0, s32 arg1) {
    return func_002E27F8(arg0 + 0xF4, arg1, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14), 2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x160), f32 *, 4));
}
