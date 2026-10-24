#include "ps2/prelude.h"

extern s32 func_002842E8();
extern s32 func_00281198();
extern s32 func_00319C70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 func_00285258();

s32 func_00284378(void *arg0) {
    if (func_002842E8() == 0) {
        return 0;
    }
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x14);
}

void func_002843B0(void *arg0, void *arg1) {
    func_00281198();
    M2C_FIELD(arg0, s32 *, 0x34) = func_00319C70(0, 0, 0, 0, 0);
    M2C_FIELD(arg0, u8 *, 0x32) = (u8) M2C_FIELD(arg1, u8 *, 0x1C);
}

s32 func_00284408(void) {
    func_00285258();
    return 1;
}
