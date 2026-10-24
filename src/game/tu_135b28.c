#include "ps2/prelude.h"

extern s32 func_00188B68(void *);

void func_00135B28(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x32C);
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        func_00188B68(temp_4 + 0x290);
    }
}
