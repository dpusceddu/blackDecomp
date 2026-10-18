#include "auto/prelude.h"

extern s32 func_002A90E8(s32);

void func_001AE538(void *arg0) {
    func_002A90E8(M2C_FIELD(M2C_FIELD(arg0, void **, 0xD540), s32 *, 0x58));
    M2C_FIELD(arg0, void **, 0xD540) = NULL;
}
