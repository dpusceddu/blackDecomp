#include "ps2/prelude.h"

extern s32 func_001EC970();
extern s32 func_001EC768();
extern s128 D_004432A0;

void func_001ED0A0(void *arg0, void *arg1) {
    void *temp_16;

    if (arg1 != NULL) {
        temp_16 = M2C_FIELD(arg1, void **, 0x110);
        if ((temp_16 != NULL) && (M2C_FIELD(temp_16, s32 *, 0x18) != -1)) {
            func_001EC970(arg0, func_001EC768(), M2C_FIELD(temp_16, s32 *, 0x18), D_004432A0);
        }
    }
}
