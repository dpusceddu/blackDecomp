#include "ps2/prelude.h"

extern s32 func_001092F8();
extern s32 func_00288930(s32);
extern s32 func_00108540(s32, M2C_UNK, s32, s16);
extern s32 D_0040F4C4;
extern s16 func_0012D508(void *arg0);
extern void * D_0040F4D0;

void func_0012A480(void) {
    s32 temp_2;

    temp_2 = func_001092F8();
    func_00288930(temp_2);
    func_00108540(D_0040F4C4, 0xC, temp_2, func_0012D508(D_0040F4D0));
}
