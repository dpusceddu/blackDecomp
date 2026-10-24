#include "ps2/prelude.h"

extern s32 func_0020B8E8(void *);
extern void * D_0040F544;
extern void * D_0040F0E0;
extern void func_001040D8(void *arg0, s32 arg3, s32, s32);
extern s32 D_003BC3CC;

void func_00104050(void) {
    func_0020B8E8(D_0040F544);
}

void func_00104078(s32 arg0) {
    void *temp_3;

    temp_3 = D_0040F0E0 + 0x20220;
    func_001040D8(temp_3, arg0, D_003BC3CC, M2C_FIELD(temp_3, s32 *, 0x210) != 0);
}

s32 func_001040C0(void) {
    return M2C_FIELD(D_0040F0E0, s32 *, 0x20F70);
}
