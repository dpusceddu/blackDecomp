#include "auto/prelude.h"

extern s32 func_001D7BB8();
extern void * func_0015BF38(s32);
extern void * D_0040F510;
extern s32 func_001D63A8(s32, s32, void *);

void func_001E80C0(s64 arg0, s32 *arg1) {
    s32 temp_2;
    void *temp_6;

    temp_2 = func_001D7BB8(func_0015BF38(*arg1 + 0x280), arg0);
    if (temp_2 != 0) {
        temp_6 = M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), void **, 0xC);
        func_001D63A8(M2C_FIELD(temp_6, s32 *, 0x1BE0), temp_2, temp_6);
    }
}
