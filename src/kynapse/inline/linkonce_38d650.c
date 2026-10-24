#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406618[];
const char rodata_00406618[104] __asm__("D_00406618") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim11IConstraintZPFv_PQ24Kaim11IConstraint" "\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EC08;
extern s32 func_00370188();

s32 * func_0038D650(void) {
    if (D_0040EC08 == 0) {
        func_00370188(&D_0040EC08, D_00406618);
    }
    return &D_0040EC08;
}
