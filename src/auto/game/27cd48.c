#include "auto/prelude.h"

s32 func_0027CD48(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x60);
    return M2C_FIELD(temp_3, s64 *, 0x10) >= M2C_FIELD(temp_3, s64 *, 8);
}
