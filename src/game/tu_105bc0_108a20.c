#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_0040EAE4;
extern M2C_UNK D_003F40B0;

s32 func_00108A20(void) {
    return M2C_FIELD(((D_0040EAE4 * 4) + ((s32) &D_003F40B0)), s32 *, 0);
}
