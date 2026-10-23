#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BF70;
extern s32 func_00370760();
extern s32 D_0040EC48;

s32 * func_003713D0(void) {
    if (D_0049BF70 == 0) {
        func_00370760();
        func_00370168(&D_0049BF70, "19__builtin_type_info", &D_0040EC48);
    }
    return &D_0049BF70;
}
