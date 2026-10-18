#include "auto/prelude.h"

extern M2C_UNK * D_003EB798;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;

void func_002E9328(void *arg0, s32 arg1) {
    void *temp_4;
    void *temp_4_2;

    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003EB798;
    temp_4 = M2C_FIELD(arg0, void **, 4);
    if (temp_4 != NULL) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 8);
    if (temp_4_2 != NULL) {
        D_003C87E0(temp_4_2);
    }
    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003E0040;
    if (arg1 & 1) {
        D_003C87E0(arg0);
    }
}
