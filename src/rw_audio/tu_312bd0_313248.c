#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003131C0();
extern s32 func_00312BC8();
extern s32 func_00313F50();
extern s32 func_00313F90();
extern s32 func_00312C48();
extern void func_00313C48(void *arg0);
extern s32 func_00324E38();
extern s32 func_00324D98();
extern s32 func_00316618();
extern s32 func_003165C8();
extern s32 func_00318250(s32);
extern s32 func_00318288(s32);
extern s32 func_003183C0(s32);

void func_00313248(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 4) == func_003131C0) {
        func_00312BC8();
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003134E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003137C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003137D8);

s32 func_00313948(s32 arg0) {
    return func_003143D8(arg0, (s32) func_00313F50, M2C_FIELD(arg0, s32 *, 0x28));
}

s32 func_00313970(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_003143D8(arg0, (s32) func_00313F90, M2C_FIELD(arg0, s32 *, 0x28));
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003139A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313B18);

void * func_00313BF0(void *arg0) {
    s32 var_2;
    void *var_16;

    var_16 = arg0;
    if (var_16 == NULL) {
        var_16 = func_00312C48(0x48, 0x30808);
        var_2 = 2;
    } else {
        var_2 = 1;
    }
    M2C_FIELD(var_16, s32 *, 0x30) = var_2;
    func_00313C48(var_16);
    return var_16;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313C88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313DC8);

void func_00313E60(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) | M2C_FIELD(arg1, u8 *, 8));
}

void func_00313E88(void) {
    func_00324E38();
}

s32 func_00313EA8(s32 arg0) {
    return func_00324D98(arg0, 0);
}

void * func_00313EC8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), M2C_UNK (**)(), 0x24)();
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313F00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313F50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003141E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314278);

s32 func_00314330(s32 arg0, s32 arg1, s32 arg2) {
    func_00316618(arg0, arg1);
    func_003165C8(arg0, arg2);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003143C8);

void func_003143D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;
    s32 temp_4;
    void *var_16;

    temp_17 = arg0 + 0xC;
    var_16 = M2C_FIELD(arg0, void **, 0x10);
    if (var_16 != temp_17) {
loop_1:
        temp_4 = M2C_FIELD(var_16, s32 *, 8);
        var_16 = M2C_FIELD(var_16, void **, 4);
        if (((s32 (*)(s32, s32)) arg1)(temp_4, arg2) != 0) {
            if (var_16 != temp_17) {
                goto loop_1;
            }
        }
    }
}

s32 func_00314440(s32 arg0) {
    return (~func_00318250(arg0 + 0xC) == 0) ? 0 : arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314478);

void func_00314488(s32 arg0) {
    func_00318288(arg0 + 0xC);
}

void func_003144A8(s32 arg0) {
    func_003183C0(arg0 + 0xC);
}
