#include "ps2/prelude.h"

extern s32 func_002E1548();
extern M2C_UNK D_003DCFA0;
extern s32 func_002E1818();

M2C_UNK ** func_00171A08(M2C_UNK **arg0) {
    func_002E1548();
    *arg0 = &D_003DCFA0;
    return arg0;
}

s32 func_00171A40(void *arg0, void *arg1) {
    return func_002E1818() != 0;
}

s32 func_00171A60(void) {
    return 0;
}
