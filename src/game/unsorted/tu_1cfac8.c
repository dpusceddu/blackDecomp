#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0026A7A0();
extern s32 func_001C5F48(void *);
extern void * D_0040F4C0;

void func_001CFAC8(void *arg0) {
    func_0026A7A0();
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        func_001C5F48(D_0040F4C0);
    }
}
