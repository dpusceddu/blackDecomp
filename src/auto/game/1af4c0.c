#include "auto/prelude.h"

extern s32 func_001AF180();
extern M2C_UNK func_001CA258;
extern M2C_UNK func_001CA208;

void func_001AF4C0(void *arg0) {
    func_001AF180(arg0 + 0xCA58, 0, &func_001CA258);
    func_001AF180(arg0 + 0xCA70, 1, &func_001CA258);
    func_001AF180(arg0 + 0xCA88, 2, &func_001CA208);
    func_001AF180(arg0 + 0xCAA0, 3, NULL);
    func_001AF180(arg0 + 0xCAB8, 4, NULL);
    func_001AF180(arg0 + 0xCAD0, 5, NULL);
    func_001AF180(arg0 + 0xCAE8, 6, NULL);
}
