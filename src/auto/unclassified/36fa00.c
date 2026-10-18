#include "auto/prelude.h"

extern void ** func_00292088();

void * func_0036FA00(void) {
    return *func_00292088();
}

void * func_0036FA20(void) {
    void *temp_3;

    temp_3 = *func_00292088();
    M2C_FIELD(temp_3, s32 *, 0x14) = 1;
    M2C_FIELD(temp_3, s64 *, 0x20) = (s64) (M2C_FIELD(temp_3, s64 *, 0x20) + 1);
    return temp_3;
}
