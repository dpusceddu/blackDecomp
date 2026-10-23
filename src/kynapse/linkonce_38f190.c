#include "auto/prelude.h"

extern s32 D_0040EC20;
extern s32 func_00370188();
extern M2C_UNK D_00407068;

s32 * func_0038F190(void) {
    if (D_0040EC20 == 0) {
        func_00370188(&D_0040EC20, &D_00407068);
    }
    return &D_0040EC20;
}
