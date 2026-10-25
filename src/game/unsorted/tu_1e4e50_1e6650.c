#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void * func_001E51E0();
extern s32 func_001E63B8();
extern void * D_0040F4D0;
extern s32 func_00135550();
extern s32 func_001848C0();

s32 func_001E6650(void *arg0, s32 arg1, s64 arg2, s32 arg3) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = arg2;
    if ((M2C_FIELD(arg0, u8 *, 0x184) == 0) && (func_001E51E0(M2C_FIELD(arg0, void **, 0x16C), arg0 + 0x160, sp) != NULL)) {
        M2C_FIELD(arg0, s32 *, 0x168) = arg1;
        func_001E63B8(arg0, *(s64 *)(sp + 0), arg3);
        M2C_FIELD(arg0, s32 *, 0x180) = arg3;
        M2C_FIELD(arg0, s64 *, 0x178) = *(s64 *)(sp + 0);
        M2C_FIELD(arg0, u8 *, 0x184) = 1U;
        M2C_FIELD(arg0, f32 *, 0x174) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    }
    return 0;
}

s32 func_001E66F0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 1;
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E67B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6948);

s16 func_001E69E0(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0x62);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E69E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6AF0);

s32 func_001E6AF8(s32 arg0, void *arg1) {
    s32 temp_2;

    if (((M2C_FIELD(arg1, s32 *, 0x38C) ^ 1) != 0) && (func_00135550(arg1) != 0)) {
        temp_2 = func_001848C0(func_00135550(arg1) + 0x6F0);
        return (func_001E6B70(arg0, temp_2) == 0) ? 0 : temp_2;
    }
    return 0;
}

s32 func_001E6B70(s32 arg0, void *arg1) {
    s32 var_2;

    var_2 = 0;
    if (arg1 != NULL) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x348) != 0;
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E7078);

s32 func_001E7118(void *arg0) {
    s32 var_5;

    var_5 = 1;
    if (!((M2C_FIELD(arg0, f32 *, 0x30) + M2C_FIELD(arg0, f32 *, 0x34)) < M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_5 = 0;
    }
    return var_5;
}


void func_001E75F0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 1;
}
