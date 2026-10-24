#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_0049BF50;
extern s32 func_00370760();
extern s32 D_0040EC48;

s32 * func_003712F0(void) {
    if (D_0049BF50 == 0) {
        func_00370760();
        func_00370168(&D_0049BF50, "16__ptmf_type_info", &D_0040EC48);
    }
    return &D_0049BF50;
}
