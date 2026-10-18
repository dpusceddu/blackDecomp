#include "auto/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_003F5328;

s32 func_00155208(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 * 2;
    return M2C_FIELD((arg0 + temp_5), u16 *, 0) == M2C_FIELD((temp_5 + ((s32) &D_003F5328)), u16 *, 0);
}
