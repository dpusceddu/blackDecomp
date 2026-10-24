#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00283C38();
extern s32 func_00283E78();
extern s32 func_002842E8();
extern s32 func_00328140(void *, s32);
extern s32 func_003281B0(s32);
extern s32 func_00328180(s32);
extern s32 func_00328108(s32, s32);
extern s32 func_00281198();
extern s32 func_00319C70(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 func_00285258();
extern s32 func_00284BF0();
extern s32 func_002851E0();
extern s32 func_00319E28(s32, s32);
extern f32 func_003106F0(s32, M2C_UNK, M2C_UNK);
extern s32 func_00319DE0(s32, M2C_UNK);

void func_00283648(void) {

}

void func_00283650(void) {
    func_00283C38();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00283670);

s32 func_00283858(s32 arg0, s32 arg1) {
    return func_00283E78(arg0, arg1, 0);
}

void func_00283878(void) {
    func_00284298();
}

void func_00283898(void) {
    func_002842E8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002838B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00283A78);

void func_00283AC0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00283AC8);

void func_00283B10(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), M2C_FIELD(arg1, s32 *, 0x18));
}

void func_00283B38(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x35) == 0) {
        func_003281B0(M2C_FIELD(arg0, s32 *, 0x38));
    }
}

void func_00283B60(void *arg0) {
    func_00328180(M2C_FIELD(arg0, s32 *, 0x38));
}

void func_00283B80(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB4) = fparg0;
}

void func_00283B90(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), f32 *, 0xB8) = fparg0;
}

void func_00283BA0(void *arg0, s32 arg1) {
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 0x38);
    M2C_FIELD(temp_6, u16 *, 0x5C) = (u16) (M2C_FIELD(temp_6, u16 *, 0x5C) | 0x80);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x18) = arg1;
}

void func_00283BC0(void *arg0, s32 arg1) {
    u16 temp_2;
    u16 var_2;

    func_00328108(M2C_FIELD(arg0, s32 *, 0x38), arg1 != 0);
    temp_2 = M2C_FIELD(arg0, u16 *, 0x30);
    if (arg1 != 0) {
        var_2 = temp_2 | 0x80;
    } else {
        var_2 = temp_2 & 0xFF7F;
    }
    M2C_FIELD(arg0, u16 *, 0x30) = var_2;
}

void func_00283C10(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

void func_00283C18(void *arg0) {
    func_00328180(M2C_FIELD(arg0, s32 *, 0x38));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00283C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00283E78);

s32 func_00284298(void *arg0) {
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 **, 0x30) = 1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002842E8);

s32 func_00284378(void *arg0) {
    if (func_002842E8() == 0) {
        return 0;
    }
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), void **, 0x30), s32 *, 0x14);
}

void func_002843B0(void *arg0, void *arg1) {
    func_00281198();
    M2C_FIELD(arg0, s32 *, 0x34) = func_00319C70(0, 0, 0, 0, 0);
    M2C_FIELD(arg0, u8 *, 0x32) = (u8) M2C_FIELD(arg1, u8 *, 0x1C);
}

s32 func_00284408(void) {
    func_00285258();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284428);

s32 func_00284628(s32 arg0, s32 arg1) {
    return func_00284BF0(arg0, arg1, 0);
}

void func_00284648(void) {
    func_00285190();
}

void func_00284668(void) {
    func_002851E0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284688);

void func_002848A0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002848A8);

void func_00284918(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284920);

void func_00284990(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 0x18));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002849C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284A10);

void func_00284A60(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x7C) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1);
    }
}

void func_00284A98(void *arg0, f32 fparg0) {
    s32 temp_4;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), f32 *, 0x80) = fparg0;
    temp_4 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), s32 *, 0x60);
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1);
    }
    M2C_FIELD(arg0, f32 *, 0x24) = fparg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284B28);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Vtable_003E26E8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00284BB0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->field_34, s8 *, 0x84) = (s8) temp_f0;
    return temp_f0;
}

s32 func_00284BD0(Recovered_Vtable_003E26E8 *arg0, f32 fparg0) {
    s32 temp_f0;

    temp_f0 = (s32) (fparg0 * 255.0f);
    M2C_FIELD(arg0->field_34, s8 *, 0x87) = (s8) temp_f0;
    return temp_f0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00284BF0);

s32 func_00285190(void *arg0) {
    func_00319DE0(M2C_FIELD(arg0, s32 *, 0x34), 0);
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002851E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00285258);

s32 func_00285510(s32 arg0) {
    s32 var_3;
    s32 var_5;
    void *var_4;

    var_4 = arg0 + 0xE00;
    var_5 = 0;
    var_3 = 0;
    do {
        if (M2C_FIELD(var_4, u8 *, 0x35) != 0) {
            var_5 |= 1 << var_3;
        }
        var_3 += 1;
        var_4 += 0x3C;
    } while (var_3 < 0x18);
    return var_5;
}
