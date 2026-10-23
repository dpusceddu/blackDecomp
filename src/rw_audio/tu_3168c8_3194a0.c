#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00319828(void *, s32, s32, s32, void *);

s32 func_003194A0(void *arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    M2C_FIELD(arg0, s32 *, 0x44) = 3;
    M2C_FIELD(arg0, s32 *, 0x48) = arg3;
    M2C_FIELD(arg0, void **, 0x4C) = arg4;
    return func_00319828(arg0, arg1, arg2, arg3, arg4);
}
