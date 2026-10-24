#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0027FCF8(void *, void *, s32);

void * func_001D7BB8(void *arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = (s64) arg1;
    return func_0027FCF8(M2C_FIELD(arg0, void **, 0x88), sp, 0);
}
