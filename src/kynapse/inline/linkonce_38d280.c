#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049B940;
extern s32 func_0038D390();
extern s32 func_00370168();
extern s32 D_0049B950;

s32 * func_0038D280(void) {
    if (D_0049B940 == 0) {
        func_0038D390();
        func_00370168(&D_0049B940, "Q24Kaim11IPathFinder", &D_0049B950);
    }
    return &D_0049B940;
}
