#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003C15C0;
extern M2C_UNK D_00445DA0;

s32 func_0029C6C8(s32 arg0) {
    M2C_UNK *var_4;

    D_003C15C0 = 1;
    var_4 = &D_00445DA0;
    do {
        M2C_FIELD(var_4, s32 *, 0) = 0;
        M2C_FIELD(var_4, s32 *, 4) = 0;
        M2C_FIELD(var_4, s32 *, 8) = 0;
        M2C_FIELD(var_4, s32 *, 0xC) = 0;
        var_4 = (M2C_UNK *) (((s8 *) var_4) + 0x334);
    } while ((s32) var_4 < (s32) ((void *) (((s8 *) &D_00445DA0) + 0x3340)));
    return 1;
}
