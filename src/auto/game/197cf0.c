#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00182318(s32, M2C_UNK);
extern s32 func_00188148(void *, M2C_UNK);

void func_00197CF0(void *arg0) {
    func_00193980();
    func_00182318(M2C_FIELD(arg0, void **, 0) + 0x810, 0);
    func_00188148(M2C_FIELD(arg0, void **, 0) + 0x290, 1);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x4C) = 5;
    M2C_FIELD(arg0, s8 *, 8) = 0;
}
