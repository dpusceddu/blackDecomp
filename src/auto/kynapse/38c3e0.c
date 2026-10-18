#include "auto/prelude.h"

extern s32 D_00451220;
extern M2C_UNK * func_0038C5F8(M2C_UNK *arg0);
extern M2C_UNK D_003EAB88;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002E1E08;

void * func_0038C3E0(void) {
    if (D_00451220 == 0) {
        func_0038C5F8(&D_003EAB88);
        D_00451220 = 1;
        func_0035E690(&func_002E1E08);
    }
    return &D_003EAB88;
}
