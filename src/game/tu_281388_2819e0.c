#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00280EE0(void *, s32);

s32 func_002819E0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_4;
    u32 temp_17;

    var_16 = arg0;
    temp_17 = var_16 + 0xE00;
    var_4 = var_16;
    do {
        func_00280EE0((void *) var_4, arg1);
        var_16 += 0x38;
        temp_2 = (u32) var_16 < temp_17;
        var_4 = var_16;
    } while (temp_2 != 0);
    return temp_2;
}
