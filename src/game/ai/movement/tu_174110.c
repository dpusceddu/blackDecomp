#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 D_003BCF08;
extern s32 D_003BCF0C;
extern s32 D_003BCF10;
extern u8 D_0040D9C4;

void func_00174110(void) {
    D_003BCF08 = 0;
    D_003BCF0C = 0;
    D_003BCF10 = 0;
    D_0040D9C4 = 1;
}
