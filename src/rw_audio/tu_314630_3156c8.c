#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003152C8(s32 *);

s32 func_003156C8(s32 arg0, void *arg1) {
    M2C_UNK *var_16;
    s32 *var_4;
    void *temp_17;

    temp_17 = (void *) (((s8 *) arg1) + 0x20);
    var_16 = M2C_FIELD(arg1, M2C_UNK **, 0x20);
    if (var_16 != temp_17) {
        var_4 = (s32 *) (((s8 *) var_16) + -0x50);
        do {
            var_16 = *var_16;
            func_003152C8(var_4);
            var_4 = (s32 *) (((s8 *) var_16) + -0x50);
        } while (var_16 != temp_17);
    }
    return 0;
}
