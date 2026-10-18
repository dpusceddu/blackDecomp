#include "auto/prelude.h"
#include "types_ghidra.h"

extern void func_00204F90();
extern s32 func_002071C8(void *arg0);
extern s32 func_00207938(void *arg0);
extern s32 func_002789C0();
extern s32 D_003BDCC0;

void func_00204EA0(void) {
    func_00204F90();
}

s32 func_00204EC0(void *arg0) {
    func_002071C8(M2C_FIELD(arg0, void **, 0x60));
    func_002071C8(M2C_FIELD(arg0, void **, 0x60) + 0x1C);
    func_00207938(M2C_FIELD(arg0, void **, 0x64));
    return 1;
}

s32 func_00204F00(s32 arg0) {
    return func_002789C0(arg0, 0xA, 0x1E, 0x1E, D_003BDCC0, 0x1880);
}
