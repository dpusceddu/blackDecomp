#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00364B78(s32, s8 *, void *, s32);
extern void * D_003D6944;

s32 func_00364DA8(s8 *arg0, void *arg1, s32 arg2) {
    return func_00364B78((s32) D_003D6944, arg0, arg1, arg2);
}
