#include "auto/prelude.h"

extern s32 D_003BFAD4;
extern s32 D_003BFAD8;

s32 func_00251A60(void) {
    s32 temp_2;
    s32 temp_3;

    temp_2 = D_003BFAD4;
    temp_3 = D_003BFAD8 * 4;
    D_003BFAD8 = 0;
    D_003BFAD4 = temp_2 + temp_3;
    return temp_2;
}
