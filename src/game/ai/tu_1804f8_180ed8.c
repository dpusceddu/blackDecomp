#include "include_asm.h"
#include "ps2/prelude.h"

extern void *func_0013D400(void *);
extern void *func_00188F80(void *);
extern s32 func_00178F18(void *);
extern s32 func_00188F58(void *);

s32 func_00180ED8(s32 arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x100);
    if (M2C_FIELD(temp_5, s32 *, 0x14) == 1) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    if (M2C_FIELD(temp_5, u8 *, 0x71) == 0) {
        goto block_6;
    }
    return 0;
block_6:
    return arg0 + 0x20;
}

void func_00180F10(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

s32 func_00180F18(s8 *arg0) {
    *arg0 = 0;
    return 1;
}

// Unmatched: 00180F28: conditional return join and saved-register allocation.
#ifdef NON_MATCHING
s32 func_00180F28(void *state) {
    void *owner;
    void *handler;
    void *vtable;
    void *adjusted;
    s32 context;
    s32 result = 1;
    if (M2C_FIELD(state, u8 *, 0) == 0) {
        owner = M2C_FIELD(state, void **, 4);
        if (func_00178F18(func_00188F80((s8 *) owner + 0x150)) == 0) goto activate;
        handler = func_0013D400(M2C_FIELD(state, void **, 4));
        vtable = M2C_FIELD(handler, void **, 0x34);
        adjusted = (s8 *) handler + M2C_FIELD(vtable, s16 *, 0x18);
        vtable = (s8 *) vtable + 0x18;
        context = func_00188F58((s8 *) M2C_FIELD(state, void **, 4) + 0x150);
        if (M2C_FIELD(vtable, s32 (**)(void *, void *, s32), 4)(adjusted, state, context) != 0) {
activate:
            M2C_FIELD(state, u8 *, 0) = 1;
            return 1;
        }
        result = 0;
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180ed8", func_00180F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180ed8", func_00180FD8);
void func_00180FE0(void *state) {
    void *handler;
    void *vtable;
    M2C_FIELD(state, u8 *, 0) = 0;
    handler = func_0013D400(M2C_FIELD(state, void **, 4));
    vtable = M2C_FIELD(handler, void **, 0x34);
    M2C_FIELD(vtable, void (**)(void *, void *), 0x2C)(
        (s8 *) handler + M2C_FIELD(vtable, s16 *, 0x28), state);
}
