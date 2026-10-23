#include "auto/prelude.h"

extern s32 D_00450FD0;
extern s32 func_0038B078();
extern M2C_UNK D_003E6028;
extern s32 func_0035E690();
extern M2C_UNK func_002DC9F0;

M2C_UNK * func_0038B098(void) {
    if (D_00450FD0 == 0) {
        func_0038B078(&D_003E6028);
        D_00450FD0 = 1;
        func_0035E690(&func_002DC9F0);
    }
    return &D_003E6028;
}
