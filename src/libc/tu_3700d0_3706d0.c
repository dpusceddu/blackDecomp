#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_0049BF20;
extern s32 * func_00370090();
extern s32 D_0040EC40;

s32 * func_003706D0(void) {
    if (D_0049BF20 == 0) {
        func_00370090();
        func_00370168(&D_0049BF20, "8bad_cast", &D_0040EC40);
    }
    return &D_0049BF20;
}
