#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00103908();
extern void * D_0040F0E0;
extern s32 func_001038A8();
extern s32 func_0014CCB0(void *, f32);
extern void ** D_0040F4D0;
extern s32 func_0012D5A8();

void func_0012D910(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x38) != 0) && (func_00103908(D_0040F0E0) == 0) && (func_001038A8(D_0040F0E0) == 0)) {
        func_0014CCB0(arg0 + 0x230, M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
    }
    if ((M2C_FIELD(arg0, s32 *, 8) != M2C_FIELD(arg0, s32 *, 4)) || (M2C_FIELD(arg0, s32 *, 0) != 0x1C)) {
        func_0012D5A8(arg0);
    }
}

extern s32 func_0012D5A8(void*);
extern s32 func_0012DD78(void*);
extern void func_001084A8(void*, s32, s16);
extern void* D_0040F4C4;
extern s16 func_0012E018(void*);
extern s16 func_0012E070(void*);
extern void func_0012F610(void*);
extern void* D_0040F534;
extern void func_0012F1B8(void*);
extern void* D_0040F538;
extern void func_0014CC90(void*);
extern s32 func_001797E0(void*);
extern s32 D_0040F4D8;
extern s32 func_001B7E60(void*);
extern s32 func_001B74F0(void*);

s32 func_0012D9A0(void* arg0) {
    s32 temp_16;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32*, 0);
    if (temp_3 >= 2) {
        if (temp_3 >= 8) {
            if (temp_3 != 0x1C) { return 1; }
            goto block_6;
        }
        if (func_0012D5A8(arg0) == 0) { return 0; }
    block_6:
        func_0012DD78(arg0);
        func_001084A8(D_0040F4C4, 4, func_0012E018(arg0));
        func_001084A8(D_0040F4C4, 0xA, func_0012E070(arg0));
        func_0012F610(D_0040F534);
        func_0012F1B8(D_0040F538);
        M2C_FIELD(arg0, s32*, 0xC) = 0;
        M2C_FIELD(arg0, s32*, 0x10) = 0;
        M2C_FIELD(arg0, s32*, 8) = -1;
        M2C_FIELD(arg0, s32*, 0) = 0x37;
        func_0014CC90((u8*)arg0 + 0x230);
        func_001797E0(M2C_FIELD(arg0, void**, 0x24));
        temp_16 = D_0040F4D8;
        func_001B7E60(temp_16 + 0x696F0);
        func_001B74F0(temp_16 + 0x66290);
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_12d458_12d910", func_0012DAB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_12d458_12d910", func_0012DD78);
