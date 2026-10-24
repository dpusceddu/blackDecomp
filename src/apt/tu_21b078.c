#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00250058(void *, s32);
extern void * D_0043DEE0;

s32 * func_0021B078(s32 arg0) {
    s32 *temp_2;

    temp_2 = func_00250058(D_0043DEE0, arg0 + 4);
    *temp_2 = arg0;
    return (s32 *) (((s8 *) temp_2) + 4);
}
