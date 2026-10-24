#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 D_0049BE90;
extern s32 * func_00389100();
extern void func_00370168(void *, char *, void *); /* __rtti_si */
extern s32 D_0040EBC0;

s32 func_00394B30(void) {
    if (D_0049BE90 == 0) {
        func_00389100();
        func_00370168(&D_0049BE90, "Q24Kaim6CSound", &D_0040EBC0);
    }
    return (s32) &D_0049BE90;
}
