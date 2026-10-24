#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001FC558(void *, s32, s32);

s32 func_001FC490(void *arg0) {
    f32 var_f1;

    var_f1 = M2C_FIELD(arg0, f32 *, 0x15C) / M2C_FIELD(arg0, f32 *, 0x158);
    if (var_f1 > 1.0f) {
        var_f1 = 1.0f;
    }
    return func_001FC558(arg0, (s32) ((f32) M2C_FIELD(arg0, u16 *, 0x144) * (1.0f - var_f1)) & 0xFFFF, (s32) M2C_FIELD(arg0, u16 *, 0x146));
}
