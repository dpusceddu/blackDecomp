#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00312C70();
extern M2C_UNK D_0040A2D8;
extern s32 func_00311278();
extern M2C_UNK func_003112E0;
extern M2C_UNK * func_00312C48();
extern s32 func_00315440();
extern s32 func_003159C8();
extern s32 func_00316698();
extern s32 func_003166F8();

s32 func_003151D8(void *arg0) {
    s32 var_6;

    var_6 = (M2C_FIELD(arg0, s32 *, 4) != 0) ? 0x2C : 0x1C;
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0) {
        var_6 += M2C_FIELD(arg0, s32 *, 0x14);
    }
    return var_6;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315208);

s32 func_00315278(s32 arg0, s32 arg1, s32 arg2) {
    if (func_00316618(arg0, arg1) != 0) {
        return (func_003165C8(arg0, arg2) == 0) ? 0 : arg0;
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003152C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315378);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0031E0E0(s32, void *, s32, void *, s32);
extern s32 func_00315718(s32, void *, void *);

void * func_00315380(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(void * *)(sp + 4) = NULL;
    func_0031E0E0(0, NULL, (s32) func_00315718, sp, 1);
    return *(void * *)(sp + 4);
}

void func_003153C0(M2C_UNK **arg0, M2C_UNK *arg1, s32 arg2) {
    M2C_UNK *temp_4;

    if (M2C_FIELD(arg0, s32 *, 0x58) & 1) {
        temp_4 = M2C_FIELD(arg0, M2C_UNK **, 0x38);
        if (temp_4 != NULL) {
            func_00312C70(temp_4);
        }
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & 0xFFFFFFFE);
    }
    M2C_FIELD(arg0, M2C_UNK **, 0x38) = arg1;
    M2C_FIELD(arg0, s32 *, 0x34) = arg2;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003155D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003155E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003156C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003156C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003159C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315DC0);

void * func_00315DE8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_4;
    s32 var_18;
    void *var_17;

    var_17 = arg0;
    var_18 = arg1;
    if (var_17 == NULL) {
        var_17 = func_00315380(&D_0040A2D8);
    }
    if (var_18 == 0) {
        *(s32 *)(sp + 0) = 0;
        *(s32 *)(sp + 4) = M2C_FIELD(var_17, s32 *, 0x40);
        func_00311278(&func_003112E0, sp);
        var_18 = *(s32 *)(sp + 0);
    }
    temp_4 = M2C_FIELD(var_17, s32 *, 0x44);
    if ((temp_4 != 0) && (M2C_FIELD(arg5, M2C_UNK **, 0x50) == NULL)) {
        M2C_FIELD(arg5, M2C_UNK **, 0x50) = func_00312C48(temp_4, 0x30806);
        M2C_FIELD(arg5, s32 *, 0x54) = (s32) (M2C_FIELD(arg5, s32 *, 0x54) | 8);
    }
    M2C_FIELD(arg5, s32 *, 0x58) = var_18;
    M2C_FIELD(arg5, void **, 0xC) = var_17;
    if (func_00315440(var_17, arg5 + 0x2C) == 0) {
        func_003159C8(arg5, arg5 + 0x10, 0);
    }
    if (arg4 != 0) {
        if (M2C_FIELD(arg5, u8 *, 0x39) == 1) {
            M2C_FIELD(arg5, s32 *, 0x54) = (s32) (M2C_FIELD(arg5, s32 *, 0x54) | 2);
        }
    }
    return arg5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315F18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00315FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316180);

s32 func_00316190(void *arg0) {
    s32 (*temp_2)();

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s32 (**)(), 0x1C);
    if (temp_2 == NULL) {
        return 0;
    }
    return temp_2();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003161C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003162D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003163F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003164D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00316598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003165C0);

s32 func_003165C8(s32 arg0, s32 arg1) {
    func_00316698(arg0);
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFD);
    return arg0;
}

s32 func_00316618(s32 arg0, s32 arg1) {
    func_003166F8(arg0);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFE);
    return arg0;
}

s32 func_00316668(s32 arg0) {
    func_003166F8();
    func_00316698(arg0);
    return arg0;
}
