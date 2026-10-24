#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001C08B0(M2C_UNK *arg0);

void func_001C0840(void *arg0, M2C_UNK *arg1) {
    func_001C08B0(arg1);
    *arg1 = M2C_FIELD(arg0, M2C_UNK **, 4);
    M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
    M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + 1);
}
