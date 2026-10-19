#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00187B10(void *);

s32 func_00187D30(void *arg0, s128 arg1, s128 arg2) {
    s32 temp_v0;

    temp_v0 = func_00187B10(arg0);
    M2C_FIELD(arg0, s128 *, 0x4D0) = (s128) arg2;
    M2C_FIELD(arg0, s128 *, 0x4C0) = (s128) arg1;
    return temp_v0;
}
