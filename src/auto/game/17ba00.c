#include "auto/prelude.h"

extern s32 func_00174320();
extern void func_0017B3C0(void *arg0);

void func_0017BA00(void *arg0, s32 arg1) {
    s32 *temp_2;

    temp_2 = M2C_FIELD(arg0, s32 **, 0xC);
    if ((temp_2 != NULL) && (*temp_2 == arg1)) {
        M2C_FIELD(arg0, s32 **, 0xC) = NULL;
    }
    func_00174320();
}

void func_0017BA38(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_0017B3C0(arg0 + 0x10);
}
