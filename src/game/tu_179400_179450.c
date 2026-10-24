#include "ps2/prelude.h"

extern s32 func_001797E0(void *arg0);

s32 func_00179450(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x70);
    if (temp_4 != NULL) {
        M2C_FIELD(arg0, void **, 0x70) = NULL;
        func_001797E0(temp_4);
    }
    M2C_FIELD(arg0, s8 *, 0x74) = 0;
    return 1;
}

void func_00179490(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x74) = 1;
}
