#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407538[];
const char rodata_00407538[88] __asm__("D_00407538") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000" "Q24Kaimt10CMetaClass2ZQ24Kaim11IConstraintZPFv_PQ24Kaim11IConstraint" "\000\000\000\000";
extern s32 D_0049BBC0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();
extern M2C_UNK D_00407610;

s32 * func_00390AE0(void) {
    if (D_0049BBC0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_00407538);
        }
        func_00370168(&D_0049BBC0, &D_00407610, &D_0040EBC0);
    }
    return &D_0049BBC0;
}
