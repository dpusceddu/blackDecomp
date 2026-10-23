#include "auto/prelude.h"

extern s32 D_0049AB78;
extern s32 * func_0038AFB8();
extern s32 func_00370168();
extern s32 D_0049AB88;

s32 * func_0038AF58(void) {
    if (D_0049AB78 == 0) {
        func_0038AFB8();
        func_00370168(&D_0049AB78, "Q24Kaim15CPathWayManager", &D_0049AB88);
    }
    return &D_0049AB78;
}
