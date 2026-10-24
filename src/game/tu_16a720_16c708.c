/* Translation unit tu_16a720 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00169BF0();
extern s32 func_00169EB8();
extern s32 func_00273888();
extern void * D_0040F4D0;
extern M2C_UNK func_0016CD58;
extern s32 func_0016D1F8(M2C_UNK, M2C_UNK);

void func_0016C708(void) {
    func_00169BF0();
}

/* Assembly between the functions: func_0016C728 (704 bytes), func_0016C9E8 (360 bytes), func_0016CB50 (312 bytes), func_0016CC88 (104 bytes) */

s32 func_0016CCF0(void) {
    func_00169EB8();
    return 1;
}

/* Assembly between the functions: func_0016CD10 (8 bytes) */

void func_0016CD18(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11C) = 1;
    func_00273888(D_0040F4D0 + 0x4920, arg0 + 0x160, &func_0016CD58, arg0);
}

/* Assembly between the functions: func_0016CD58 (112 bytes), func_0016CDC8 (552 bytes), func_0016CFF0 (520 bytes), func_0016D1F8 (1384 bytes), func_0016D760 (56 bytes), func_0016D798 (56 bytes) */

void func_0016D7D0(void) {
    func_0016D1F8(1, 0xFFFF);
}
