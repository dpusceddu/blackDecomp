#include "auto/prelude.h"

extern s32 func_001623B8();
extern void * func_00135550();
extern s32 func_001790D0();
extern void * D_0040F4D4;
extern s32 func_0013D8A0();

void func_00162420(void *arg0) {
    s64 *temp_2;

    temp_2 = func_001623B8();
    M2C_FIELD(arg0, s64 **, 0x24) = temp_2;
    if ((temp_2 != NULL) && (func_00135550(temp_2) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), s32 *, 0x80) == 1)) {
        M2C_FIELD(arg0, s32 *, 0x30) = func_001790D0(D_0040F4D4 + 0xFA8, arg0);
        func_0013D8A0(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), arg0);
    }
}
