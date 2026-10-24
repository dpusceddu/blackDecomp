#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00280C90(void *, s32);
extern f32 func_001ED820(void *);
extern void * D_0040F510;

f32 func_001E4260(void *arg0, s32 arg1, s32 arg2) {
    f32 var_f0;

    func_00280C90(arg0, arg2);
    if (arg2 != 0) {
        var_f0 = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), void **, 0x2C));
    } else {
        var_f0 = 1.0f;
    }
    M2C_FIELD(arg0, f32 *, 0x37C) = var_f0;
    return var_f0;
}
