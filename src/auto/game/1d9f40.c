#include "auto/prelude.h"

extern s32 func_001DAD08(void *arg0);

void func_001D9F40(void **arg0) {
    func_001DAD08(*arg0);
}

s32 func_001D9F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x24) * M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0xE0);
}
