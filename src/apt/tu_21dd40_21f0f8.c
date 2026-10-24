/* Translation unit apt/tu_21dd40 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00251A60();
extern s32 func_0035CFD8(s32, s32, s32);
extern s32 D_003BE904;
extern s32 func_0035CCD8(s32);
extern s32 func_0023DB58(void *, s32);

void func_0021F0F8(void) {
    func_00251A60();
}

/* Assembly between the functions: func_0021F118 (8 bytes), func_0021F120 (168 bytes), func_0021F1C8 (4352 bytes), func_002202C8 (776 bytes), func_002205D0 (600 bytes), func_00220828 (864 bytes), func_00220B88 (384 bytes), func_00220D08 (112 bytes), func_00220D78 (344 bytes), func_00220ED0 (384 bytes) */

s32 func_00221050(s32 arg0, s32 arg1) {
    return func_0035CFD8(arg1, D_003BE904, func_0035CCD8(D_003BE904)) == 0;
}

/* Assembly between the functions: func_00221098 (80 bytes) */

void func_002210E8(void) {

}

void func_002210F0(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) + 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}

void func_00221140(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) - 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}

/* Assembly between the functions: func_00221190 (256 bytes), func_00221290 (144 bytes) */

void func_00221320(void) {

}

void func_00221328(void) {

}
