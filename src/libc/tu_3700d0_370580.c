#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BEF0;
extern s32 func_00370760();
extern M2C_UNK D_0040EC48;

s32 * func_00370580(void) {
    if (D_0049BEF0 == 0) {
        func_00370760();
        func_00370168(&D_0049BEF0, "16__user_type_info", &D_0040EC48);
    }
    return &D_0049BEF0;
}
