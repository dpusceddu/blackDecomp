#include "ps2/prelude.h"

extern s32 func_00204F00();
extern void func_00206110(s32, void *);
extern void func_00206218(void *arg0, void *);

void func_00205830(void *arg0) {
    func_00204F00();
    M2C_FIELD(arg0, s32 *, 0xB8) = 2;
    func_00206110(arg0 + 0x60, arg0);
    func_00206218(arg0 + 0x7C, arg0);
}
