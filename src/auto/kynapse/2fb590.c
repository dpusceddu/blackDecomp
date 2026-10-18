#include "auto/prelude.h"

extern M2C_UNK * D_003EE580;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;

void func_002FB590(void *arg0, s32 arg1) {
    s32 temp_4_3;
    void *temp_4;
    void *temp_4_2;
    void *temp_4_4;

    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003EE580;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_4_2 != NULL) {
        D_003C87E0(temp_4_2);
    }
    temp_4_3 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_4_3 != 0) {
        D_003C87E0(temp_4_3 - 0x10);
    }
    temp_4_4 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_4_4 != NULL) {
        D_003C87E0(temp_4_4);
    }
    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003E0040;
    if (arg1 & 1) {
        D_003C87E0(arg0);
    }
}
