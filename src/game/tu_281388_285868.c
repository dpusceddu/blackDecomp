#include "auto/prelude.h"

extern s32 func_00281F88();

s32 func_00285868(void) {
    return 1;
}

void func_00285870(void) {

}

s32 func_00285878(void) {
    return 1;
}

s32 func_00285880(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    return func_00281F88(arg0);
}
