/* Translation unit tu_1e4e50 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00280100(void *, s32);
extern void * D_0040F510;
extern void * D_0040F50C;
extern s32 func_001D7BB8();
extern void * func_0015BF38(s32);
extern s32 func_001D63A8(s32, s32, void *);
extern s32 func_001EFD30();

s32 func_001E79F0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 8) != 3) {
        func_00280100(D_0040F510, M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(D_0040F50C, s32 *, 0x948) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 3;
    }
    return 1;
}

/* Assembly between the functions: func_001E7A50 (8 bytes), func_001E7A58 (944 bytes), func_001E7E08 (80 bytes), func_001E7E58 (616 bytes) */

void func_001E80C0(s64 arg0, s32 *arg1) {
    s32 temp_2;
    void *temp_6;

    temp_2 = func_001D7BB8(func_0015BF38(*arg1 + 0x280), arg0);
    if (temp_2 != 0) {
        temp_6 = M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), void **, 0xC);
        func_001D63A8(M2C_FIELD(temp_6, s32 *, 0x1BE0), temp_2, temp_6);
    }
}

/* Assembly between the functions: func_001E8120 (160 bytes) */

s32 func_001E81C0(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1AC);
    if (temp_3 != 1) {
        if (temp_3 < 2) {
            if (temp_3 != 0) {
                return 0;
            }
            goto block_6;
        }
        if (temp_3 != 2) {
            if (temp_3 == 3) {
block_6:
                M2C_FIELD(arg0, s32 *, 0x1AC) = 1;
                goto block_7;
            }
            /* Duplicate return node #11. Try simplifying control flow for better match */
            return 0;
        }
        goto block_9;
    }
block_7:
    if (func_001EFD30(D_0040F510) != 0) {
        M2C_FIELD(arg0, s32 *, 0x1AC) = 2;
block_9:
        return 1;
    }
    return 0;
}

s32 func_001E8248(void) {
    return 1;
}

/* Assembly between the functions: func_001E8250 (88 bytes), func_001E82A8 (1128 bytes), func_001E8710 (136 bytes) */

void func_001E8798(void) {

}
