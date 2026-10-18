#include "auto/prelude.h"

extern s32 D_0049AB68;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038AEE0(void) {
    if (D_0049AB68 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
        }
        func_00370168(&D_0049AB68, "Q34Kaim15CPathWayManager11CPathWayMap", &D_0040EBC0);
    }
    return &D_0049AB68;
}
