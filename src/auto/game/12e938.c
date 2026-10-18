#include "auto/prelude.h"

extern s32 func_00168618(s32, s32, u8, void *);
extern s32 D_0040F4F4;
extern void * D_0040F4D0;

void func_0012E938(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 4);
    func_00168618(D_0040F4F4, M2C_FIELD(temp_2, s32 *, 0x20), M2C_FIELD(temp_2, u8 *, 0x24), D_0040F4D0 + 0x30);
}

s32 func_0012E978(void *arg0) {
    return M2C_FIELD(arg0, s8 *, 0x39) != 0;
}
