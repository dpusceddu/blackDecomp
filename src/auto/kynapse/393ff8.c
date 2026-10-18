#include "auto/prelude.h"

extern s32 D_0049BDD0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408888;
extern s32 func_00370168();

s32 * func_00393FF8(void) {
    if (D_0049BDD0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408888);
        }
        func_00370168(&D_0049BDD0, "Q24Kaim4CGap", &D_0040EBC0);
    }
    return &D_0049BDD0;
}
