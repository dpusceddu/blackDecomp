#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003C40A0;
extern s32 D_003C40B8;
extern s32 D_003C4098;

s32 func_002CE0F8(s32 arg0) {
    D_003C40A0 = arg0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce0f8", func_002CE108);

s32 func_002CE110(s32 arg0) {
    D_003C40B8 = arg0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ce0f8", func_002CE120);

s32 func_002CE140(void) {
    return D_003C4098;
}

void func_002CE150(void) {

}

void func_002CE158(void) {

}
