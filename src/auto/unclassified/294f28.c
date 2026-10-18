#include "auto/prelude.h"

extern s32 func_00371610(s32);
extern s32 func_003716F8(s32);

s32 func_00294F28(void *arg0) {
    func_00371610(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}

s32 func_00294F50(void *arg0) {
    func_003716F8(M2C_FIELD(arg0, s32 *, 0x40) + 0x68);
    return 1;
}
