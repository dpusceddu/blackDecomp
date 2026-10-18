#include "auto/prelude.h"

extern M2C_UNK D_003E12F8;
extern s32 func_002486D8();
extern s32 func_00250198();
extern s32 D_0043DEE0;

void func_003866F8(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x18);
    }
}

void func_00386760(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x18);
    }
}

void func_003867C8(u16 *arg0, s32 arg1) {
    void *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        func_002486D8(temp_4, 3);
    }
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x1C);
    }
}
