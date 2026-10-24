#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BF30;
extern s32 func_00370760();
extern s32 D_0040EC48;

s32 * func_00371210(void) {
    if (D_0049BF30 == 0) {
        func_00370760();
        func_00370168(&D_0049BF30, "17__array_type_info", &D_0040EC48);
    }
    return &D_0049BF30;
}
