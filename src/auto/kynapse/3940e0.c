#include "auto/prelude.h"

extern s32 D_0049BDE0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408888;
extern s32 func_00370168();
extern s32 D_0049BDF0;

s32 * func_003940E0(void) {
    if (D_0049BDE0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408888);
        }
        func_00370168(&D_0049BDE0, "Q24Kaim13EntityTracker", &D_0040EBC0);
    }
    return &D_0049BDE0;
}

s32 * func_00394158(void) {
    if (D_0049BDF0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408888);
        }
        func_00370168(&D_0049BDF0, "Q34Kaim20CGapDynamicAvoidance16CCandidateTarget", &D_0040EBC0);
    }
    return &D_0049BDF0;
}
