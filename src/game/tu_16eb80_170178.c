#include "ps2/prelude.h"

extern s32 func_00171A08();
extern M2C_UNK D_003DCF60;
extern s32 func_00171A40();

M2C_UNK ** func_00170178(M2C_UNK **arg0) {
    func_00171A08();
    *arg0 = &D_003DCF60;
    return arg0;
}

s32 func_001701B0(void *arg0, void *arg1) {
    return func_00171A40(arg0, arg1) != 0;
}

s32 func_001701D0(void) {
    return 1;
}
