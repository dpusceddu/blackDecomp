#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00123C90(s32 *, void *, void *);

s32 func_00123BF0(s32 *arg0, void *arg1, s32 arg2, s32 arg3) {
    return *func_00123C90(arg0, (void *)7, arg1) >= 2;
}
