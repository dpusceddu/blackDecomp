#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0023EB78();
extern s32 func_002405E8();
extern s32 func_00241928(void *);
extern void * func_00250058(s32, s32);
extern s32 D_0043DEE0;
extern s32 func_00241128();
extern s32 func_00241AD8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023EB78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023ECC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023ED28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023EE00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023EF98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023F018);

void * func_0023F020(void *arg0) {
    void *temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg0, void **, 0x4C);
    if (temp_3 != NULL) {
        M2C_FIELD(temp_3, void **, 0x50) = (void *) M2C_FIELD(arg0, void **, 0x50);
    }
    temp_3_2 = M2C_FIELD(arg0, void **, 0x50);
    if (temp_3_2 != NULL) {
        M2C_FIELD(temp_3_2, void **, 0x4C) = (void *) M2C_FIELD(arg0, void **, 0x4C);
    }
    M2C_FIELD(arg0, void **, 0x4C) = NULL;
    M2C_FIELD(arg0, void **, 0x50) = NULL;
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023F058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023F858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023FAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023FBE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023FE48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002405E8);

s32 func_002406A0(s32 arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    func_0023EB78(M2C_FIELD(arg0, s32 *, 0), arg1, 0, (s32) sp, (s32) (sp + 4));
    return func_002405E8(arg0, *(s32 *)(sp + 4));
}

s32 func_002406E0(s32 arg0, s32 arg1) {
    return func_002406A0(arg0, M2C_FIELD(arg1, s32 *, 0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240700);

s32 * func_00240758(s32 *arg0) {
    *arg0 = func_00241928(func_00250058(D_0043DEE0, 4));
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002407F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240B08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00240F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241128);

s32 func_00241228(s32 arg0) {
    s32 temp_4;
    s32 var_v0;

    var_v0 = func_00241128(arg0, 0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_4 != 0) {
        var_v0 = func_00241AD8(temp_4, 3);
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
    return var_v0;
}

s32 func_00241268(s32 *arg0) {
    return *arg0;
}

s32 func_00241270(s32 arg0, s32 arg1, s32 arg2) {
    return func_002405E8(arg0, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002418D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002418D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241928);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00241AD8);
