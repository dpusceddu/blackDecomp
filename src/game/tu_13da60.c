#include "auto/prelude.h"

extern s32 func_0016ABA8(void *, s32, s32, s32);
extern s32 func_00182A40(s32);
extern s32 func_00180678(s32);
extern s32 func_00185E38(s32);
extern s32 func_00181470(s32);
extern s32 func_00183EF8(s32);

void func_0013DA60(void *arg0) {
    s32 temp_5;

    if (M2C_FIELD(arg0, u8 *, 0x1FC1) == 0) {
        temp_5 = M2C_FIELD(arg0, s32 *, 0x1FC4);
        if (temp_5 != 0) {
            func_0016ABA8(arg0 + 0x1F90, temp_5, M2C_FIELD(arg0, s32 *, 0x1FC8), M2C_FIELD(arg0, s32 *, 0x7C));
        }
        M2C_FIELD(arg0, u8 *, 0x1FC1) = 1U;
    }
}

void func_0013DAB0(s32 arg0) {
    func_00182A40(arg0 + 0x810);
    func_00180678(arg0 + 0xB30);
    func_00185E38(arg0 + 0x90);
    func_00181470(arg0 + 0xEC0);
}

void func_0013DAF0(s32 arg0) {
    func_00183EF8(arg0 + 0x6F0);
}
