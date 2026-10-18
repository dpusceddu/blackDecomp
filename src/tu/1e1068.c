#include "auto/prelude.h"

extern s32 func_001DEEB8();
extern s32 func_001E0D28();
extern s32 func_001E0F28(void *);
extern s32 func_001E0E70(void *);
extern s32 func_001E0A30(void *);

void func_001E1068(void *arg0) {
    u8 sp[8];
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_3 != -1) {
        if (temp_3 == 0) {
            func_001DEEB8(sp, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, u8 *, 0x24), 0);
        }
        M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - 1);
    }
}

void func_001E10C0(void *arg0) {
    func_001E0D28();
    func_001E0F28(arg0);
    func_001E0E70(arg0);
    func_001E0A30(arg0);
}
