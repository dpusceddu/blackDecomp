#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BA10;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406700;
extern s32 func_00370168();

s32 * func_0038DE90(void) {
    if (D_0049BA10 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406700);
        }
        func_00370168(&D_0049BA10, "Q34Kaimt8CVarList1ZPQ24Kaim14CBaseAllocator9CIterator", &D_0040EBC0);
    }
    return &D_0049BA10;
}
