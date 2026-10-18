#include "auto/prelude.h"

extern void func_00204F90();
extern s32 func_00206B30(s32);
extern s32 func_00206F08(s32);
extern s32 func_00204FF0();

void func_002060B8(void) {
    func_00204F90();
}

s32 func_002060D8(s32 arg0) {
    func_00206B30(arg0 + 0x60);
    func_00206F08(arg0 + 0x88);
    return 1;
}

void func_00206110(void) {
    func_00204FF0();
}
