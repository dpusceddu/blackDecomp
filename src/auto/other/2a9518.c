#include "auto/prelude.h"

extern s32 func_002A8688();
extern s32 func_002A7DD0();
extern s32 func_002A8DA0();
extern s32 func_002A8860();
extern void * func_002D0910();

void * func_002A9518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) == 1) {
        func_002A8688();
        func_002A7DD0(arg0);
    } else {
        func_002A8DA0(arg0);
        func_002A8860(arg0);
    }
    func_002D0910(arg0 + 0x10C, arg0 + 0x124, 8);
    return arg0;
}
