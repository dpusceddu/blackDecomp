#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00209C60(s32);
extern void func_0020D1A8(void *, s32);
extern void * D_0040F544;
extern s32 func_00209C88(void *, M2C_UNK);
extern s32 func_00209CC0(void *);

void func_0020D910(void *arg0) {
    s32 temp_4;
    void *temp_4_2;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x44);
    if (temp_4 != 0) {
        M2C_FIELD(arg0, s32 *, 0x28) = func_00209C60(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 0x48);
    if (temp_4_2 != NULL) {
        func_0020D910(temp_4_2);
    }
}

void func_0020D960(void *arg0) {
    s32 temp_5;
    void *temp_4;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x40);
    if (temp_5 != 0) {
        func_0020D1A8(D_0040F544 + 0xE90, temp_5);
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
    }
    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    if (temp_4 != NULL) {
        func_00209C88(temp_4, 0);
        func_00209CC0(M2C_FIELD(arg0, void **, 0x44));
        M2C_FIELD(arg0, void **, 0x44) = NULL;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020D9C0);
