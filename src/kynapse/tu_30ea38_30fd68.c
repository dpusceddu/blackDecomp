#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E75D0();
extern M2C_UNK D_00455E18;
extern M2C_UNK func_0030EA38;
extern M2C_UNK * D_00455F28;
extern M2C_UNK D_003E00E0;
extern M2C_UNK D_003F1430;

void func_0030FD68(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E75D0(&D_00455E18, "CEntityManager", &func_0030EA38, 0, 1, 1);
            return;
        }
        D_00455F28 = &D_003E00E0;
    }
}

void * func_0030FDC8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003F1430;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, s8 *, 0x11) = 0;
    M2C_FIELD(arg0, s8 *, 0x12) = 0;
    M2C_FIELD(arg0, s8 *, 0x13) = 0;
    return arg0;
}
