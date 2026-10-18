#include "auto/prelude.h"

extern s32 func_003110B0();
extern s32 func_00323188();

s32 func_0037B8A8(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, void ***, 0x48) = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x48);
    return func_003110B0(arg0, M2C_FIELD(arg1, s32 *, 0x54), M2C_FIELD(arg1, s32 *, 0x58));
}

s32 func_0037B8E8(s32 arg0, s32 arg1) {
    return func_00323188(arg0, M2C_FIELD(arg0, s32 *, 0x40), 2, arg1);
}
