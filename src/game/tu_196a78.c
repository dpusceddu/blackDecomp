#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00193988();

void func_00196A78(void *arg0, void *arg1) {
    func_00193980();
    M2C_FIELD(arg0, s32 *, 8) = 0;
    if ((arg1 != NULL) && (M2C_FIELD(arg1, s32 *, 0) == 4)) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    }
}

void func_00196AC8(void) {
    func_00193988();
}

void func_00196AE8(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 8);
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, s32 *, 0x380) == arg1)) {
        M2C_FIELD(arg0, void **, 8) = NULL;
    }
}
