#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BBD0;
extern s32 D_0040EC30;
extern s32 func_00370188();
extern M2C_UNK D_004075A8;
extern s32 func_00370168();

s32 * func_00390A68(void) {
    if (D_0049BBD0 == 0) {
        if (D_0040EC30 == 0) {
            func_00370188(&D_0040EC30, &D_004075A8);
        }
        func_00370168(&D_0049BBD0, "Q24Kaim15CHeuristicClass", &D_0040EC30);
    }
    return &D_0049BBD0;
}
