#include "auto/prelude.h"

extern s32 func_00174B58(s32, s32);
extern s32 func_00174BA0(s32, s32);

s32 func_0018E448(void) {
    return 1;
}

void func_0018E450(void) {

}

void func_0018E458(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    if (arg1 != 0) {
        func_00174B58(arg1, M2C_FIELD(arg0, s32 *, 4));
    }
}

void func_0018E488(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_4 != 0) {
        func_00174BA0(temp_4, M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
}
