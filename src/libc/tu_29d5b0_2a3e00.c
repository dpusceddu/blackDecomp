#include "auto/prelude.h"

extern s32 func_002919F8();

s32 func_002A3E00(void *arg0) {
    s64 temp_4;

    temp_4 = M2C_FIELD(arg0, s64 *, 8);
    func_002919F8(temp_4, temp_4);
    return 0;
}
