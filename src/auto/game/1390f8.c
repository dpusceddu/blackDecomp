#include "auto/prelude.h"

extern s32 func_00139980(void *);
extern s32 func_00135C50();
extern s32 func_0025CDF0(s32);
extern s32 D_0040F4CC;
extern s32 func_0015C100(s32);

s32 func_001390F8(s32 arg0) {
    s32 temp_2;
    void *temp_4;

    temp_4 = arg0 + 0x79A0;
    if (M2C_FIELD(temp_4, s32 *, 4) == M2C_FIELD(temp_4, s32 *, 8)) {
        temp_2 = func_00139980(temp_4);
        if (temp_2 == 0) {
            return 0;
        }
        func_00135C50(temp_2);
        goto block_4;
    }
block_4:
    return func_0025CDF0(D_0040F4CC) != 0;
}

void func_00139150(s32 arg0, s32 arg1) {
    func_0015C100(arg1 + 0x280);
}
