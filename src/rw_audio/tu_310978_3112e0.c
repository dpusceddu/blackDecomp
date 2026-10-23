#include "auto/prelude.h"

s32 func_003112E0(s32 *arg0, void *arg1) {
    if (*arg0 == M2C_FIELD(arg1, s32 *, 4)) {
        M2C_FIELD(arg1, s32 **, 0) = arg0;
        return 0;
    }
    return 1;
}
