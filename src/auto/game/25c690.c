#include "auto/prelude.h"

extern s32 func_0025CA10();

void func_0025C690(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg1, s32 *, 0xB4);
    if (temp_5 != 0) {
        func_0025CA10(arg0, temp_5);
    }
}
