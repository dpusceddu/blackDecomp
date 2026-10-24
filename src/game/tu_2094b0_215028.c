#include "ps2/prelude.h"

extern s32 D_003BE858;
extern void * D_0040F0E0;

void func_00215028(void) {
    u8 temp_2;

    D_003BE858 = 0;
    temp_2 = M2C_FIELD(D_0040F0E0, u8 *, 0x20164);
    if (temp_2 == 1) {
        D_003BE858 = (s32) temp_2;
    }
}
