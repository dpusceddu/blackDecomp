#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00171918(void *, s32);

void func_001718D0(void *arg0, s32 *arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0x7C) == 3) {
        M2C_FIELD(arg0, s32 *, 0x7C) = 1;
    }
    if (M2C_FIELD(arg0, s32 *, 0x7C) == 2) {
        func_00171918(arg0, 1);
    }
}
