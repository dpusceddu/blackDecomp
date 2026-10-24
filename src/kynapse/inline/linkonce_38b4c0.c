#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049B010;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038B4C0(void) {
    if (D_0049B010 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, "Q24Kaim7CObject");
        }
        func_00370168(&D_0049B010, "Q24Kaim7CAction", &D_0040EBC0);
    }
    return &D_0049B010;
}
