#include "auto/prelude.h"

extern s32 func_003131C0();
extern s32 func_00312BC8();

void func_00313248(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == func_003131C0) {
        func_00312BC8();
    }
}
