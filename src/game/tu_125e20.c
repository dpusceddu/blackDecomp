#include "ps2/prelude.h"

extern s32 func_00165B98();
extern s32 func_00165BB0();

void func_00125E20(void) {

}

void func_00125E28(void) {

}

void func_00125E30(void) {

}

void func_00125E38(void) {

}

s32 func_00125E40(void) {
    func_00165B98();
    return 1;
}

void func_00125E60(void *arg0) {
    void *temp_4;

    func_00165BB0();
    temp_4 = M2C_FIELD(arg0, void **, 0xB0);
    if (temp_4 != NULL) {
        func_00125E60(temp_4);
    }
}
