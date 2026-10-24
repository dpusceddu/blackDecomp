#include "ps2/prelude.h"

extern s32 D_0049B090;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

void * func_0038C318(void) {
    if (D_0049B090 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
        }
        func_00370168(&D_0049B090, "Q24Kaim6CBrain", &D_0040EBC0);
    }
    return &D_0049B090;
}
