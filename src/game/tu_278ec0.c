#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_002740E8(void *, void *);

void * func_00278EC0(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_5;
    void *temp_2;

    temp_5 = arg1 * 0x10;
    temp_2 = (void *) (((s8 *) func_002740E8(M2C_FIELD(arg0, s32 *, 0x2C) + temp_5 + 4, (void *) temp_5)) + 8);
    M2C_FIELD(temp_2, s32 *, 0x38) = arg2;
    return temp_2;
}
