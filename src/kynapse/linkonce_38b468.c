#include "auto/prelude.h"

extern s32 D_0045120C;
extern s32 func_0038B448();
extern M2C_UNK D_003E68E8;
extern s32 func_0035E690();
extern M2C_UNK func_002DFEF0;

M2C_UNK * func_0038B468(void) {
    if (D_0045120C == 0) {
        func_0038B448(&D_003E68E8);
        D_0045120C = 1;
        func_0035E690(&func_002DFEF0);
    }
    return &D_003E68E8;
}
