#include "auto/prelude.h"

s32 func_003485E8(u32 *arg0, u32 *arg1) {
    u32 temp_3;
    u32 temp_4;

    temp_4 = *arg0;
    temp_3 = *arg1;
    if (temp_3 >= temp_4) {
        return (temp_4 >= temp_3) ? 0 : -1;
    }
    return 1;
}
