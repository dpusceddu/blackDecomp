#include "ps2/prelude.h"

extern s32 D_0049B9B0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00406700;
extern s32 func_00370168();
extern s32 D_0049B9C0;
extern s32 D_0049B970;
extern M2C_UNK D_00406710;

s32 * func_0038D9E0(void) {
    if (D_0049B9B0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00406700);
        }
        func_00370168(&D_0049B9B0, "Q24Kaimt8CVarList1ZPQ24Kaim14CFreeListBlock", &D_0040EBC0);
    }
    return &D_0049B9B0;
}

s32 * func_0038DA58(void) {
    if (D_0049B9C0 == 0) {
        if (D_0049B970 == 0) {
            if (D_0040EBC0 == 0) {
                func_00370188(&D_0040EBC0, &D_00406700);
            }
            func_00370168(&D_0049B970, &D_00406710, &D_0040EBC0);
        }
        func_00370168(&D_0049B9C0, "Q24Kaim9CFreeList", &D_0049B970);
    }
    return &D_0049B9C0;
}
