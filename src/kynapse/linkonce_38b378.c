#include "auto/prelude.h"

extern s32 D_0049ABE8;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00405E48;
extern s32 func_00370168();

s32 * func_0038B378(void) {
    if (D_0049ABE8 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00405E48);
        }
        func_00370168(&D_0049ABE8, "Q24Kaim8CPathWay", &D_0040EBC0);
    }
    return &D_0049ABE8;
}
