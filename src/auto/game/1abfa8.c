#include "auto/prelude.h"

extern s32 func_001ABEE0(s32, s32, s32);
extern s32 D_0040F50C;
extern s32 func_001AE0A8(void *arg0);
extern void func_001AE090(void *arg0, s32 arg1);

void func_001ABFA8(s32 arg0, s32 arg1) {
    func_001ABEE0(D_0040F50C, arg0, arg1);
}

s32 func_001ABFD8(s32 arg0) {
    s32 temp_2;
    void *temp_16;

    temp_16 = arg0 + 0x8F0;
    temp_2 = func_001AE0A8(temp_16);
    func_001AE090(temp_16, temp_2);
    return temp_2;
}
