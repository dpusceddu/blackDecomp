#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_0049BF00;
extern s32 * func_00370580();
extern s32 D_0049BEF0;

s32 * func_003704F8(void) {
    if (D_0049BF00 == 0) {
        func_00370580();
        func_00370168(&D_0049BF00, "14__si_type_info", &D_0049BEF0);
    }
    return &D_0049BF00;
}
