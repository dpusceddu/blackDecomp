#include "auto/prelude.h"

extern s32 D_0049BA20;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406700;
extern s32 func_00370168();

s32 * func_0038DF40(void) {
    if (D_0049BA20 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406700);
        }
        func_00370168(&D_0049BA20, "Q34Kaimt8CVarList1ZPQ24Kaim14CFreeListBlock5CCell", &D_0040EBC0);
    }
    return &D_0049BA20;
}
