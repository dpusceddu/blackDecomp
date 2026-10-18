#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003605F0(s32, void *, void *, s32);
extern void * D_003D6944;

s32 func_00360800(void *arg0, void *arg1, s32 arg2) {
    return func_003605F0((s32) D_003D6944, arg0, arg1, arg2);
}
