#include "auto/prelude.h"

extern s32 func_002E2D40();
extern s32 func_002E3578();
extern s32 func_002E3630();
extern s32 func_002E36E8();

void * func_002E13B8(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *temp_16;

    temp_16 = func_002E2D40(arg0);
    if (arg1 != NULL) {
        func_002E3578(temp_16, arg1);
    }
    if (arg2 != NULL) {
        func_002E3630(temp_16, arg2);
    }
    if (arg3 != NULL) {
        func_002E36E8(temp_16, arg3);
    }
    return temp_16;
}
