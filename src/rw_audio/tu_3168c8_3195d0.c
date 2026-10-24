#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00319828(void *, s32, s32, s32, void *);
extern s32 func_00319628(s32, s32, s32, s32, void *);

s32 func_003195D0(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    M2C_FIELD(arg0, void **, 0x4C) = arg3;
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    M2C_FIELD(arg0, s32 *, 0x44) = 3;
    return func_00319828(arg0, arg1, 0xC, (s32) func_00319628, arg0);
}
