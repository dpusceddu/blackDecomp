/* Translation unit kynapse/tu_2eef88 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_002F35B0();
extern M2C_UNK D_00451658;
extern M2C_UNK func_002EEF88;
extern M2C_UNK * D_00451768;
extern M2C_UNK D_003EC200;
extern M2C_UNK * D_003EC1C8;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;

void func_002F09A8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00451658, "CFindNearestData", &func_002EEF88);
            return;
        }
        D_00451768 = &D_003EC200;
    }
}

/* Assembly between the functions: func_002F0A00 (48 bytes) */

void func_002F0A30(void *arg0, s32 arg1) {
    void *temp_4;
    void *temp_4_2;
    void *temp_4_3;

    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003EC1C8;
    temp_4 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_4 != NULL) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 0x10);
    if (temp_4_2 != NULL) {
        D_003C87E0(temp_4_2);
    }
    temp_4_3 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_4_3 != NULL) {
        D_003C87E0(temp_4_3);
    }
    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003E0040;
    if (arg1 & 1) {
        D_003C87E0(arg0);
    }
}

/* Assembly between the functions: func_002F0AD8 (192 bytes), func_002F0B98 (232 bytes), func_002F0C80 (232 bytes) */

void func_002F0D68(void) {
    func_002F09A8(1, 0xFFFF);
}

void func_002F0D88(void) {
    func_002F09A8(0, 0xFFFF);
}
