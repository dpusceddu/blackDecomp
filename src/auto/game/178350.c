#include "auto/prelude.h"

extern s32 func_0017B8A8();
extern void * D_0040F4D4;
extern s32 func_00177C78();

void func_00178350(void *arg0, s128 arg1, f32 fparg0) {
    s32 temp_2;

    M2C_FIELD(arg0, f32 *, 0x50) = fparg0;
    M2C_FIELD(arg0, s128 *, 0) = arg1;
    temp_2 = func_0017B8A8(D_0040F4D4 + 0x1290);
    if (temp_2 != 0) {
        func_00177C78(temp_2, arg0);
    }
}
