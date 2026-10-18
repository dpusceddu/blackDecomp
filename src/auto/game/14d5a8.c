#include "auto/prelude.h"

extern void * func_0014EC90(s32);
extern void func_0014D5F0(void *arg0, void *arg1);

void func_0014D5A8(void *arg0) {
    void *temp_2;

    temp_2 = func_0014EC90(M2C_FIELD(arg0, s32 *, 8));
    if (temp_2 != NULL) {
        func_0014D5F0(arg0, temp_2);
        return;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
}
