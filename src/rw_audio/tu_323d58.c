#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00316668();
extern s32 func_00312C70();

s32 func_00323D58(s32 arg0) {
    *M2C_FIELD(arg0, void ***, 0x24) = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x24);
    func_00316668(arg0);
    return func_00312C70(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00323DA0);
