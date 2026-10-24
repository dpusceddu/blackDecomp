#include "ps2/prelude.h"

extern s32 D_0049BBF0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_00390C20(void) {
    if (D_0049BBF0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
        }
        func_00370168(&D_0049BBF0, "Q34Kaim13CGraphManager9CGraphMap", &D_0040EBC0);
    }
    return &D_0049BBF0;
}
