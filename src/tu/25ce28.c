#include "auto/prelude.h"

extern s32 func_0032E1B0(s32, void *);
extern s32 func_00100290(s32, s32, M2C_UNK);
extern s32 func_00107B78();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107D20();

void func_0025CE28(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B04) = -1;
}

void func_0025CE40(s32 *arg0, void *arg1) {
    if (func_0032E1B0(*arg0, M2C_FIELD(arg1, void **, 0x34)) != 0) {
        func_00100290(*arg0, M2C_FIELD(M2C_FIELD(arg1, void **, 0x34), s32 *, 0xC), 1);
    }
}

void func_0025CE90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x3D) = 0;
    M2C_FIELD(arg0, s8 *, 0x3E) = 0;
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 1;
    func_00107B78(&D_0040F0F0, 0xB, 0x10, 0);
    M2C_FIELD(arg0, s32 *, 0x34) = func_00107D20(0x90);
}
