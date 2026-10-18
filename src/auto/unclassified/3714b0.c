#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BF90;
extern s32 func_00370760();
extern s32 D_0040EC48;

s32 * func_003714B0(void) {
    if (D_0049BF90 == 0) {
        func_00370760();
        func_00370168(&D_0049BF90, "19__pointer_type_info", &D_0040EC48);
    }
    return &D_0049BF90;
}
