#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_00443670;
extern s32 func_0035C6EC();
extern M2C_UNK D_00443660;
extern M2C_UNK D_00443678;

M2C_UNK * func_002920D8(void) {
    if (D_00443670 == 0) {
        D_00443670 = 1;
        func_0035C6EC(&D_00443660, 0, 0x10);
        M2C_FIELD(&D_00443660, M2C_UNK **, 4) = &D_00443678;
    }
    return &D_00443660;
}
