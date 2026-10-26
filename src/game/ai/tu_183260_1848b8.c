#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00175F50();
extern s32 func_00189250(void *, s32);
extern f32 func_0018E130(void *);
extern f32 func_0018E110(void *);
extern void * D_0040F4D4;

s32 func_001848B8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_001848C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_001849D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_00184B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_00184D10);

#include "ps2/recovered_types.h"
extern s32 func_00184DE0(s32 *);

void func_00184D78(s32 *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, f32 *, 8) = 3.4028235e38f;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) == 1) {
        func_00184DE0(arg0);
    }
    M2C_FIELD((void *) M2C_FIELD(arg0, s32 *, 0), s8 *, 0x284) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_00184DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_183260_1848b8", func_001851C8);

s32 func_00185318(s32 arg0, s32 arg1, s32 arg2) {
    return func_00175F50((s32) (D_0040F4D4 + 0xFA0), arg1, arg2, 0x221, M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s32 *, 0x7C), 1);
}

f32 func_00185350(s32 *state, void *target) {
    s32 selected = 0;
    s32 mode;
    f32 value;
    if (target != NULL) {
        selected = func_00189250((void *) (state[0] + 0x150), M2C_FIELD(target, s32 *, 0x380));
    }
    mode = M2C_FIELD(state, s32 *, 0x64);
    switch (mode) {
    case 0:
        value = M2C_FIELD(state, f32 *, 0x14) * func_0018E130((void *) (state[0] + 0xC94));
        break;
    case 2:
    case 3:
        if (selected != 0) {
            value = __ee_max_s(M2C_FIELD(state, f32 *, 0x10),
                M2C_FIELD(state, f32 *, 0x14) * func_0018E110((void *) (state[0] + 0xC94)));
            break;
        }
        /* Fall through. */
    case 1:
    default:
        value = M2C_FIELD(state, f32 *, 0x14) * func_0018E110((void *) (state[0] + 0xC94));
        break;
    }
    if (M2C_FIELD(state, f32 *, 0x18) >= 0.0f) {
        value = __ee_min_s(value, M2C_FIELD(state, f32 *, 0x18));
    }
    return value;
}
f32 func_00185438(s32 *state, void *target) {
    s32 selected = 0;
    s32 mode;
    if (target != NULL) {
        selected = func_00189250((void *) (state[0] + 0x150), M2C_FIELD(target, s32 *, 0x380));
    }
    mode = M2C_FIELD(state, s32 *, 0x64);
    switch (mode) {
    case 0:
        return M2C_FIELD(state, f32 *, 0x28);
    case 2:
    case 3:
        if (selected != 0) return M2C_FIELD(state, f32 *, 0x20);
        /* Fall through. */
    case 1:
    default:
        return M2C_FIELD(state, f32 *, 0x24);
    }
}
