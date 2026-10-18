#include "auto/prelude.h"

extern void * D_004494F4;

void * func_002AA288(void *arg0) {
    u8 temp_8;
    void *temp_4;
    void *temp_5;
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 0xA0);
    temp_8 = M2C_FIELD(temp_6, u8 *, 3);
    if (!(temp_8 & 3)) {
        temp_4 = temp_6 + 8;
        temp_5 = D_004494F4;
        M2C_FIELD(temp_6, void ***, 0xC) = &D_004494F4;
        M2C_FIELD(temp_5, void **, 4) = temp_4;
        D_004494F4 = temp_4;
        M2C_FIELD(temp_6, void **, 8) = temp_5;
    }
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xA0), u8 *, 3) = (u8) (temp_8 | 3);
    M2C_FIELD(arg0, u8 *, 3) = (u8) (M2C_FIELD(arg0, u8 *, 3) | 0xC);
    return arg0;
}
