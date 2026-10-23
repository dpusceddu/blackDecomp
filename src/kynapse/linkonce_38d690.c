#include "auto/prelude.h"

extern s32 D_0049B990;
extern s32 D_0049B980;
extern s32 D_0049B970;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406700;
extern s32 func_00370168();
extern M2C_UNK D_00406710;
extern M2C_UNK D_00406728;
extern s32 D_0049B9A0;

s32 * func_0038D690(void) {
    if (D_0049B990 == 0) {
        if (D_0049B980 == 0) {
            if (D_0049B970 == 0) {
                if (D_0040EBC0 == 0) {
                    func_00370188(&D_0040EBC0, &D_00406700);
                }
                func_00370168(&D_0049B970, &D_00406710, &D_0040EBC0);
            }
            func_00370168(&D_0049B980, &D_00406728, &D_0049B970);
        }
        func_00370168(&D_0049B990, "Q24Kaim15CBasicAllocator", &D_0049B980);
    }
    return &D_0049B990;
}

s32 * func_0038D760(void) {
    if (D_0049B9A0 == 0) {
        if (D_0049B980 == 0) {
            if (D_0049B970 == 0) {
                if (D_0040EBC0 == 0) {
                    func_00370188(&D_0040EBC0, &D_00406700);
                }
                func_00370168(&D_0049B970, &D_00406710, &D_0040EBC0);
            }
            func_00370168(&D_0049B980, &D_00406728, &D_0049B970);
        }
        func_00370168(&D_0049B9A0, "Q24Kaim19CPoolBasedAllocator", &D_0049B980);
    }
    return &D_0049B9A0;
}

s32 * func_0038D830(void) {
    if (D_0049B970 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406700);
        }
        func_00370168(&D_0049B970, &D_00406710, &D_0040EBC0);
    }
    return &D_0049B970;
}
