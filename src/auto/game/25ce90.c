#include "auto/prelude.h"

extern s32 func_00107B78();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107D20();

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
