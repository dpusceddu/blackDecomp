/* Translation unit tu_190ea0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0018E458();
extern s32 func_001911A8();

void func_00191010(void *arg0) {
    void *temp_3;
    void *temp_4;

    func_0018E458();
    temp_3 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    if ((M2C_FIELD(temp_3, u8 *, 0x28) == 0) && (M2C_FIELD(temp_3, s8 *, 0x29) < 0)) {
        func_001911A8(arg0);
    }
    temp_4 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(M2C_FIELD(temp_4, void **, 0x7C), s128 *, 0xA0);
    M2C_FIELD(temp_4, s8 *, 0xD24) = 0;
}

/* Assembly between the functions: func_00191070 (160 bytes) */

u8 func_00191110(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x14);
}

/* Assembly between the functions: func_00191118 (64 bytes), func_00191158 (80 bytes), func_001911A8 (200 bytes) */

s32 func_00191270(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0), s8 *, 0x29) == M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1EF4);
}
