#include "ps2/prelude.h"

extern void func_001F5928(void *arg0);
extern void * D_0040F518;
extern void func_002019A0(void *arg0, s32 arg1);

void func_001F2D70(void) {
    func_001F5928(M2C_FIELD(D_0040F518, void **, 0x14));
    func_002019A0(M2C_FIELD(D_0040F518, void **, 0x2C), 0);
}
