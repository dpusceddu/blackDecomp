#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "animation/layouts/Recovered_AnimationParameterBank.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void func_00350098(Recovered_AnimationParameterBank *);

void func_00350140(s32 *arg0) {
    s32 *var_16;
    s32 temp_4;
    s32 var_17;

    var_16 = (s32 *) (((s8 *) arg0) + 0x8C);
    var_17 = 7;
    do {
        M2C_FIELD(var_16, s32 *, -4) = 0;
        var_17 -= 1;
        M2C_FIELD(var_16, s32 *, 4) = 0;
        M2C_FIELD(var_16, f32 *, 8) = 1.0f;
        M2C_FIELD(var_16, s32 *, 0xC) = 0;
        M2C_FIELD(var_16, s32 *, 0x10) = 0;
        M2C_FIELD(var_16, s32 *, 0x18) = 0;
        M2C_FIELD(var_16, s32 *, 0x14) = 1;
        M2C_FIELD(var_16, s32 *, 0x1C) = 0;
        M2C_FIELD(var_16, s16 *, 0x20) = 0;
        temp_4 = M2C_FIELD(var_16, s32 *, 0);
        var_16 = (s32 *) (((s8 *) var_16) + 0x28);
        func_00350098((Recovered_AnimationParameterBank *) temp_4);
    } while (var_17 >= 0);
    M2C_FIELD(arg0, s16 *, 0x1C8) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003501D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003502C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00350308);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00350410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003504C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00350570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00350650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003507C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00350890);
