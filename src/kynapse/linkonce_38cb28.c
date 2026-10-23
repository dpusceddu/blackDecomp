#include "auto/prelude.h"

extern s32 D_0049B4E8;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406398;
extern s32 func_00370168();

void * func_0038CB28(void) {
    if (D_0049B4E8 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406398);
        }
        func_00370168(&D_0049B4E8, "Q24Kaim7CEntity", &D_0040EBC0);
    }
    return &D_0049B4E8;
}
