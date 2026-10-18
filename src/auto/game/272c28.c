#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002732E0(void *, void *);

s32 func_00272C28(void *arg0, void *arg1, s128 arg2, s32 *arg3) {
    M2C_FIELD(arg1, s128 *, 0) = (s128) arg2;
    M2C_FIELD(arg1, s32 **, 0x34) = arg3;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0x24) = 0;
    return func_002732E0(arg0, arg1);
}
