#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204F00();
extern s32 func_00103818(void *);
extern void * D_0040F0E0;

s32 func_002050B0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002050B8);

s32 func_00205170(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    return 1;
}

#include "ps2/recovered_types.h"
extern s32 func_00205D40(void *);
extern s32 func_002058F0(void *);
extern s32 func_00205B68(void *);
extern s32 func_00204D80(void *);
extern s32 func_00205798();

void func_00205180(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4);
    switch (temp_2) {
    case 1:
        func_00205D40(M2C_FIELD(arg0, void **, 0xC));
        return;
    case 2:
        func_002058F0(M2C_FIELD(arg0, void **, 8));
        return;
    case 3:
        func_00205B68(M2C_FIELD(arg0, void **, 0x10));
        return;
    case 4:
        func_00204D80(M2C_FIELD(arg0, void **, 0x14));
        return;
    case 5:
        func_00205798(M2C_FIELD(arg0, s32 *, 0x18), arg0);
        /* fallthrough */
    default:
        return;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00205210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00205298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002052A0);

void func_002053C0(void) {
    func_00204F00();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002053E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00205798);

s32 func_00205808(void) {
    func_00103818(D_0040F0E0);
    return 1;
}
