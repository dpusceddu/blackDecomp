#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00322DA8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0xC) = 1;
    M2C_FIELD(arg1, s32 *, 4) = -1;
    M2C_FIELD(arg1, s32 *, 0x18) = 0;
    M2C_FIELD(arg1, s32 *, 0) = -1;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 8) = 0;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    return arg0;
}
