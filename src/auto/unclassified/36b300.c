#include "auto/prelude.h"

s32 func_0036B300(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    if ((temp_5 == NULL) || (M2C_FIELD(arg0, s32 *, 4) != M2C_FIELD(temp_5, s32 *, 0x18)) || !(M2C_FIELD(temp_5, s32 *, 0x10) & 1)) {
        return 0;
    }
    return 1;
}
