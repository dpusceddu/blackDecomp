#include "auto/prelude.h"

extern s32 func_002710D8(M2C_UNK *);
extern M2C_UNK D_00440280;
extern s32 func_002CE010();

void func_002703D0(M2C_UNK *arg0) {
    func_002710D8(&D_00440280);
    func_002CE010();
    M2C_FIELD(arg0, s32 *, 0x2F8) = 0;
}
