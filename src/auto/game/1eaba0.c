#include "auto/prelude.h"

extern s32 func_0035C6EC();

s32 func_001EABA0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    func_0035C6EC(arg0, 0, 0x40);
    return 1;
}
