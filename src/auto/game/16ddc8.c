#include "auto/prelude.h"

s32 func_0016DDC8(s32 arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x22BBC);
    M2C_FIELD(arg0, void **, 0x22BBC) = (void *) M2C_FIELD(temp_2, void **, 0x1EF0);
    return (s32) temp_2;
}
