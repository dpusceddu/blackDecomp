#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00193880(void *);
extern void func_0018C168(void *);

u8 func_00181028(u8 *arg0) {
    return *arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181028", func_00181030);
// Unmatched: 00181348: loop iterator lifetimes and register scheduling.
#ifdef NON_MATCHING
s32 func_00181348(void *stack) {
    s32 count = 0x49;
    void **entry = (void **) ((s8 *) stack + 0x718);
    do {
        void *action = *entry++;
        void *vtable = M2C_FIELD(action, void **, 4);
        count--;
        M2C_FIELD(vtable, void (**)(void *), 0x14)(
            (s8 *) action + M2C_FIELD(vtable, s16 *, 0x10));
    } while (count >= 0);
    {
        u8 *state = (u8 *) stack + 0x20;
        s32 *slot = stack;
        count = 7;
        do {
            u8 *current = state;
            *slot++ = 0x4A;
            state += 0x94;
            func_00193880(current);
            count--;
        } while (count >= 0);
    }
    M2C_FIELD(stack, s32 *, 0x4C0) = 0;
    {
        u8 *movement = (u8 *) stack + 0x4C4;
        count = 0x14;
        do {
            count--;
            func_0018C168(movement);
            movement += 0x1C;
        } while (count >= 0);
    }
    M2C_FIELD(stack, s32 *, 0x710) = 0;
    return 1;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181028", func_00181348);
