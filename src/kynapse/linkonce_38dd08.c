#include "ps2/prelude.h"

extern s32 D_0049BA00;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406700;
extern s32 func_00370168();

s32 * func_0038DD08(void) {
    if (D_0049BA00 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406700);
        }
        func_00370168(&D_0049BA00, "Q34Kaimt8CVarList1ZPQ24Kaim14CBaseAllocator5CCell", &D_0040EBC0);
    }
    return &D_0049BA00;
}
