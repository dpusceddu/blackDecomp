#include "auto/prelude.h"

extern s32 * func_00123C90();
extern M2C_UNK D_0048EFA8;
extern s32 func_001050A8();
extern void * D_0040F0E0;

void func_00103B38(void) {
    s32 temp_16;
    s32 temp_17;
    s32 temp_17_2;

    temp_17 = *func_00123C90(&D_0048EFA8, 0, 0);
    if ((temp_17 != -1) || (temp_16 = *func_00123C90(&D_0048EFA8, 0, 1), (temp_16 != temp_17)) || (temp_17_2 = *func_00123C90(&D_0048EFA8, 0, 2), (temp_17_2 != temp_16)) || (*func_00123C90(&D_0048EFA8, 0, 3) != temp_17_2)) {
        func_001050A8(D_0040F0E0 + 0x20220, 0);
    }
}
