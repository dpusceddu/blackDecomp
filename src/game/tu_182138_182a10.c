#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00170670(void *, f32);

s32 func_00182A10(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
    return func_00170670(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), void **, 0x7C), void **, 0x34C), fparg0);
}
