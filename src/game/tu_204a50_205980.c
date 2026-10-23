#include "auto/prelude.h"

extern void func_00204F90();
extern s32 func_002061F0(s32);
extern s32 func_00206A00(s32);
extern s32 func_00103870(void *);
extern void * D_0040F0E0;
extern s32 func_00103818(void *);

void func_00205980(void) {
    func_00204F90();
}

s32 func_002059A0(void *arg0) {
    func_002061F0(arg0 + 0x60);
    func_00206A00(arg0 + 0x7C);
    M2C_FIELD(arg0, s32 *, 0xB8) = 2;
    if (func_00103870(D_0040F0E0) != 0) {
        func_00103818(D_0040F0E0);
    }
    return 1;
}
