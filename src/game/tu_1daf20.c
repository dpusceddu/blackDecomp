#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001DD6C0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DAF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DAFD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB088);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001DD3E0(void *);

s32 func_001DB140(void *arg0) {
    u32 temp_3;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x28);
    switch (temp_3) {
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        M2C_FIELD(arg0, u32 *, 0x28) = 5U;
        /* fallthrough */
    case 5:
        if (func_001DD3E0(M2C_FIELD(arg0, void **, 0)) != 0) {
            M2C_FIELD(arg0, u32 *, 0x28) = 2U;
        case 0:
        case 2:
            return 1;
        }
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB1B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB2B0);

void func_001DB2F0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = fparg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB2F8);

s32 func_001DB4A0(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x28);
    var_2 = temp_3 < 7;
    if ((temp_3 >= 0) && (var_2 == 0)) {
        var_2 = temp_3 < 0xA;
        if (var_2 != 0) {
            func_001DD6C0(M2C_FIELD(arg0, s32 *, 0));
            var_2 = 6;
            M2C_FIELD(arg0, s32 *, 0x28) = 6;
        }
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB4F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DB5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DBA00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DBDB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DBED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DBF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC1A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC2C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC498);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "game/layouts/Recovered_Vtable_003E26B8.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_002810A0(Recovered_Vtable_003E26B8 *);

s32 func_001DC5A8(void *arg0) {
    Recovered_Vtable_003E26B8 *var_17;
    f32 *var_16;
    s32 temp_v0;
    s32 var_18;

    var_16 = (f32 *) (((s8 *) arg0) + 0x68);
    var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) arg0) + 0x58);
    var_18 = 0;
    do {
        var_18 -= 1;
        temp_v0 = func_002810A0(var_17);
        var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) var_17) + 0x14);
        *var_16 = -1.0f;
        var_16 = (f32 *) (((s8 *) var_16) + 0x14);
    } while (var_18 >= 0);
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC6E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DC790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DCC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DCCF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DCDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DCF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD3E0);

void func_001DD4C8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD4D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD5D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD6C0);
