#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BF10;
extern s32 * func_00370090();
extern s32 D_0040EC40;

s32 * func_00370638(void) {
    if (D_0049BF10 == 0) {
        func_00370090();
        func_00370168(&D_0049BF10, "10bad_typeid", &D_0040EC40);
    }
    return &D_0049BF10;
}
