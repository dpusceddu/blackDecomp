#include "ps2/prelude.h"

extern s32 func_00183710(void *arg0, s8 arg1);

void func_001830C0(s32 *arg0, s32 arg1) {
    if (arg1 != 0) {
        *arg0 = arg1;
    }
}

void func_001830D0(void *arg0) {
    func_00183710(M2C_FIELD(arg0, void **, 0), M2C_FIELD(arg0, s8 *, 5));
}

void func_001830F0(void *arg0) {
    func_00183710(M2C_FIELD(arg0, void **, 0), M2C_FIELD(arg0, s8 *, 6));
}
