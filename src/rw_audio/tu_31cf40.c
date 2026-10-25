#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003152C8(M2C_UNK *);
extern M2C_UNK D_004586B8;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31cf40", func_0031CF40);

s32 func_0031CFC8(void) {
    return func_003152C8(&D_004586B8) != 0;
}
