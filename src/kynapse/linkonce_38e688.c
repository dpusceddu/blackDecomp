#include "auto/prelude.h"

extern s32 D_004514F0;
extern s32 func_0038E668();
extern M2C_UNK D_003EAF90;
extern s32 func_0035E690();
extern M2C_UNK func_002E7660;

M2C_UNK * func_0038E688(void) {
    if (D_004514F0 == 0) {
        func_0038E668(&D_003EAF90);
        D_004514F0 = 1;
        func_0035E690(&func_002E7660);
    }
    return &D_003EAF90;
}
