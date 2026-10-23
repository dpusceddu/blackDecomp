#include "auto/prelude.h"

extern s32 func_001A7500();
extern void * func_00135550(void *);
extern s32 func_0017F720(s32);

void func_001AC050(s32 arg0, s32 arg1) {
    func_001A7500(arg1);
}

void func_001AC070(s32 arg0, void **arg1) {
    if ((func_00135550(*arg1) != NULL) && (M2C_FIELD(func_00135550(*arg1), s32 *, 0x80) == 1)) {
        func_0017F720(func_00135550(*arg1) + 0x650);
    }
}

void func_001AC0C8(void) {

}

void func_001AC0D0(s32 arg0, void **arg1) {
    M2C_FIELD(*arg1, s8 *, 0x3B1) = 1;
}
