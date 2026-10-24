#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0031E9D8();
extern s32 func_003228D0();
extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_00458970;
extern M2C_UNK D_00458998;
extern M2C_UNK D_004589C0;
extern s32 func_00311B50(s32);

s32 func_00321F10(s32 arg0, s32 arg1, s32 arg2) {
    return func_0031E9D8(arg0, arg1, arg2, 0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00321F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322430);

s32 func_003224E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_lo;
    s32 var_2;
    s32 var_3;

    temp_lo = (s32) (arg1 >> 1) / (s8) arg3;
    var_3 = 0;
    if ((s8) arg3 == 1) {
        var_2 = func_003228D0(arg0, arg2, temp_lo);
        goto block_4;
    }
    if ((s8) arg3 == 2) {
        var_2 = func_00322A00(arg0, arg2, temp_lo);
block_4:
        var_3 = var_2;
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003225D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003227B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003228D0);

s32 func_00322A00(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322A08);

void func_00322A78(void) {
    func_00311CA0(&D_00458970);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322A98);

void func_00322B08(void) {
    func_00311CA0(&D_00458998);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322B28);

void func_00322B98(void) {
    func_00311CA0(&D_004589C0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322BB8);

void func_00322C70(void *arg0) {
    func_00311B50(M2C_FIELD(arg0, s32 *, 0x40));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322DA8);

s32 func_00322DD8(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    func_00322E00(arg0, 0, (s32) sp);
    return *(s32 *)(sp + 0);
}

s32 func_00322E00(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s32 *, 0x28);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322E18);

s32 func_00322ED8(void) {
    return 0;
}

s32 func_00322EE0(s32 arg0, s32 arg1, void *arg2) {
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 *, 0) = arg0;
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 (**)(), 4) = func_00322ED8;
    M2C_FIELD(M2C_FIELD(arg2, void **, 4), s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 0);
    return arg0;
}

s32 func_00322F10(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 4) = (s32) (arg0 + 0x50);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00322F20);

void func_00322F80(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(s32, s32), 4)(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 8));
}
