#include "ps2/prelude.h"

extern s32 D_0049BA70;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406C78;
extern s32 func_00370168();

s32 * func_0038EC30(void) {
    if (D_0049BA70 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406C78);
        }
        func_00370168(&D_0049BA70, "Q34Kaim12CTimeManager11CEntityInfo", &D_0040EBC0);
    }
    return &D_0049BA70;
}
