#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00173640(f32 *, f32);

s32 func_00141418(void *arg0) {
    return func_00173640(arg0 + 0x4E0, 2.0f);
}
