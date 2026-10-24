#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_00315790(void *, void *, void *, void *, s32, s32);
extern s32 * D_0045C0C0;

void * func_00328C08(void *arg0, void *arg1, void *arg2, s32 arg3, void *arg4) {
    return func_00315790(&D_0045C0C0, arg0, arg1, arg2, arg3, (s32) arg4);
}
