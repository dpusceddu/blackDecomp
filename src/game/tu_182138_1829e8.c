#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00192470(s32);
extern s32 func_00192EB0(void *);
extern s32 func_00193608(void *);
extern s32 func_00173640(void *, f32);
extern s32 func_00182550();

s32 func_001829E8(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x30);
    var_4 = 0;
    if ((temp_3 == 0) || (temp_3 == 8)) {
        var_4 = 1;
    }
    return var_4;
}

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00170670(void *, f32);

s32 func_00182A10(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
    return func_00170670(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), void **, 0x7C), void **, 0x34C), fparg0);
}

void func_00182A40(s32 arg0) {
    func_00192470(arg0 + 0x60);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182D58);

void func_00182D68(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x40);
    switch (temp_3) {                               /* irregular */
    case 1:
        func_00192EB0(arg0 + 0x60);
        return;
    case 2:
        func_00193608(arg0 + 0x1F0);
        break;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182DB8);

void func_00182EA8(void *arg0) {
    func_00173640(arg0 + 0x2C, 1.0f);
    func_00182550(arg0, 2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00182EF0);
