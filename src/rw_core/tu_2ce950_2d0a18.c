#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002D1530(void *, s32, u32, u32, u32);
extern M2C_UNK D_003C3370;

s32 func_002D0A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_002D1530(&D_003C3370, arg0, (u32) arg1, (u32) arg2, (u32) arg3);
}
