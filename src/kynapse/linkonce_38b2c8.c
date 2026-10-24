#include "ps2/prelude.h"

extern s32 D_0049ABD8;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00405E48;
extern s32 func_00370168();

s32 * func_0038B2C8(void) {
    if (D_0049ABD8 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00405E48);
        }
        func_00370168(&D_0049ABD8, "Q24Kaim9CScriptWP", &D_0040EBC0);
    }
    return &D_0049ABD8;
}
