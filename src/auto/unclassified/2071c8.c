#include "auto/prelude.h"

extern s32 func_00278F00();
extern void * D_003BDCC8;

s32 func_002071C8(void *arg0) {
    func_00278F00(D_003BDCC8, 0, M2C_FIELD(arg0, s32 *, 0x18));
    return 1;
}
