#include "auto/prelude.h"

extern s32 func_00275068();
extern s32 D_003BE7A0;
extern s32 func_00209E80();
extern void * func_0020BC00();
extern void * D_0040F544;
extern s32 func_00209C90();
extern s32 func_00209CC0();

void func_0020DB90(void *arg0, s32 arg1) {
    s32 temp_2;

    M2C_FIELD(arg0, s32 *, 4) = func_00275068(D_003BE7A0, (arg1 + 0x40) * 2, 4);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    if (M2C_FIELD(arg0, s32 *, 8) != -1) {
        temp_2 = func_00209E80(func_0020BC00(D_0040F544, 3), M2C_FIELD(arg0, s32 *, 8));
        func_00209C90(temp_2, M2C_FIELD(arg0, s32 *, 4));
        func_00209CC0(temp_2);
    }
}
