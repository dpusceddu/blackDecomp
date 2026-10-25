#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_2763b0", func_00276408);
