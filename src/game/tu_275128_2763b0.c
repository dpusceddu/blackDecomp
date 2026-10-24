#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00274190(void *);

s32 func_002763B0(void *arg0) {
    M2C_UNK *var_16;

    var_16 = M2C_FIELD(arg0, M2C_UNK **, 0x44);
    if (var_16 != NULL) {
        do {
            func_002763B0((void *) (((s8 *) var_16) + 8));
            var_16 = *var_16;
        } while (var_16 != NULL);
    }
    return func_00274190((void *) (((s8 *) arg0) + 0x40));
}
