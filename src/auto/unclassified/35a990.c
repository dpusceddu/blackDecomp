#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_0047A1C0;

s32 func_0035A990(void) {
    M2C_UNK *var_3;

    var_3 = &D_0047A1C0;
    do {
        M2C_FIELD(var_3, s32 *, 0) = -1;
        M2C_FIELD(var_3, s32 *, 0xC) = 0;
        var_3 = (M2C_UNK *) (((s8 *) var_3) + 0x2010);
    } while ((s32) var_3 < (s32) ((void *) (((s8 *) &D_0047A1C0) + 0x4020)));
    return 1;
}
