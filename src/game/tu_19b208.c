#include "auto/prelude.h"

extern s32 func_00188F10();
extern f32 func_001891A8();
extern s32 func_00193990();

void func_0019B208(void **arg0) {
    if ((func_00188F10(*arg0 + 0x150) == 0) || (func_001891A8(*arg0 + 0x150) < 6.0f)) {
        func_00193990(arg0, 0);
    }
}
