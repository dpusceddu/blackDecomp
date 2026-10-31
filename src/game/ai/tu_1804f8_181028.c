#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00193880(void *);
extern void func_0018C168(void *);

u8 func_00181028(u8 *arg0) {
    return *arg0;
}

// Initializes the 74-entry component table and its embedded objects.
// Original component class identities remain UNVERIFIED.
void func_00181030(void* self, void* context) {
    void** firstEntry;
    s32* slot;
    s32 remaining;
    void** entry;
    void* vtable;
    void* component;

    firstEntry = (void**)(((s8*)self) + 0x718);
    remaining = 0x49;
    slot = (s32*)(((s8*)self) + 0x83C);
    M2C_FIELD(self, void**, 0x714) = context;
    do {
        *slot = 0;
        remaining -= 1;
        slot = (s32*)(((s8*)slot) + -4);
    } while (remaining >= 0);
    M2C_FIELD(self, void**, 0x718) = (u8*)self + 0x840;
    M2C_FIELD(self, void**, 0x71C) = (u8*)self + 0x848;
    M2C_FIELD(self, void**, 0x720) = (u8*)self + 0x850;
    M2C_FIELD(self, void**, 0x724) = (u8*)self + 0x85C;
    M2C_FIELD(self, void**, 0x728) = (u8*)self + 0x864;
    M2C_FIELD(self, void**, 0x72C) = (u8*)self + 0x874;
    M2C_FIELD(self, void**, 0x730) = (u8*)self + 0x880;
    M2C_FIELD(self, void**, 0x734) = (u8*)self + 0x888;
    M2C_FIELD(self, void**, 0x738) = (u8*)self + 0x894;
    M2C_FIELD(self, void**, 0x73C) = (u8*)self + 0x8A0;
    M2C_FIELD(self, void**, 0x740) = (u8*)self + 0x8C0;
    M2C_FIELD(self, void**, 0x744) = (u8*)self + 0x8C8;
    M2C_FIELD(self, void**, 0x748) = (u8*)self + 0x8D0;
    M2C_FIELD(self, void**, 0x74C) = (u8*)self + 0x8E0;
    M2C_FIELD(self, void**, 0x750) = (u8*)self + 0x910;
    M2C_FIELD(self, void**, 0x754) = (u8*)self + 0x930;
    M2C_FIELD(self, void**, 0x758) = (u8*)self + 0x940;
    M2C_FIELD(self, void**, 0x75C) = (u8*)self + 0x980;
    M2C_FIELD(self, void**, 0x760) = (u8*)self + 0x988;
    M2C_FIELD(self, void**, 0x764) = (u8*)self + 0x990;
    M2C_FIELD(self, void**, 0x768) = (u8*)self + 0x9C0;
    M2C_FIELD(self, void**, 0x76C) = (u8*)self + 0x9E0;
    M2C_FIELD(self, void**, 0x770) = (u8*)self + 0x9E8;
    M2C_FIELD(self, void**, 0x774) = (u8*)self + 0xA10;
    M2C_FIELD(self, void**, 0x778) = (u8*)self + 0xA1C;
    M2C_FIELD(self, void**, 0x77C) = (u8*)self + 0xA30;
    M2C_FIELD(self, void**, 0x780) = (u8*)self + 0xA50;
    M2C_FIELD(self, void**, 0x784) = (u8*)self + 0xA60;
    M2C_FIELD(self, void**, 0x788) = (u8*)self + 0xAB0;
    M2C_FIELD(self, void**, 0x78C) = (u8*)self + 0xAC0;
    M2C_FIELD(self, void**, 0x790) = (u8*)self + 0xAE8;
    M2C_FIELD(self, void**, 0x794) = (u8*)self + 0xAF4;
    M2C_FIELD(self, void**, 0x798) = (u8*)self + 0xAFC;
    M2C_FIELD(self, void**, 0x79C) = (u8*)self + 0xB04;
    M2C_FIELD(self, void**, 0x7A0) = (u8*)self + 0xB10;
    M2C_FIELD(self, void**, 0x7A4) = (u8*)self + 0xB18;
    M2C_FIELD(self, void**, 0x7A8) = (u8*)self + 0xB20;
    M2C_FIELD(self, void**, 0x7AC) = (u8*)self + 0xB28;
    M2C_FIELD(self, void**, 0x7B0) = (u8*)self + 0xB30;
    M2C_FIELD(self, void**, 0x7B4) = (u8*)self + 0xB40;
    M2C_FIELD(self, void**, 0x7B8) = (u8*)self + 0xB70;
    M2C_FIELD(self, void**, 0x7BC) = (u8*)self + 0xB90;
    M2C_FIELD(self, void**, 0x7C0) = (u8*)self + 0xBB0;
    M2C_FIELD(self, void**, 0x7C4) = (u8*)self + 0xBC0;
    M2C_FIELD(self, void**, 0x7C8) = (u8*)self + 0xBD0;
    M2C_FIELD(self, void**, 0x7CC) = (u8*)self + 0xC00;
    M2C_FIELD(self, void**, 0x7D0) = (u8*)self + 0xC10;
    M2C_FIELD(self, void**, 0x7D4) = (u8*)self + 0xC40;
    M2C_FIELD(self, void**, 0x7D8) = (u8*)self + 0xC80;
    M2C_FIELD(self, void**, 0x7DC) = (u8*)self + 0xC8C;
    M2C_FIELD(self, void**, 0x7E0) = (u8*)self + 0xCA0;
    M2C_FIELD(self, void**, 0x7E4) = (u8*)self + 0xCF0;
    M2C_FIELD(self, void**, 0x7E8) = (u8*)self + 0xD0C;
    M2C_FIELD(self, void**, 0x7EC) = (u8*)self + 0xD1C;
    M2C_FIELD(self, void**, 0x7F0) = (u8*)self + 0xD24;
    M2C_FIELD(self, void**, 0x7F4) = (u8*)self + 0xD30;
    M2C_FIELD(self, void**, 0x7F8) = (u8*)self + 0xD70;
    M2C_FIELD(self, void**, 0x7FC) = (u8*)self + 0xD7C;
    M2C_FIELD(self, void**, 0x800) = (u8*)self + 0xD90;
    M2C_FIELD(self, void**, 0x804) = (u8*)self + 0xDC0;
    M2C_FIELD(self, void**, 0x808) = (u8*)self + 0xDCC;
    M2C_FIELD(self, void**, 0x80C) = (u8*)self + 0xDD4;
    M2C_FIELD(self, void**, 0x810) = (u8*)self + 0xDDC;
    M2C_FIELD(self, void**, 0x814) = (u8*)self + 0xDE4;
    M2C_FIELD(self, void**, 0x818) = (u8*)self + 0xDF0;
    M2C_FIELD(self, void**, 0x81C) = (u8*)self + 0xE20;
    M2C_FIELD(self, void**, 0x820) = (u8*)self + 0xE28;
    M2C_FIELD(self, void**, 0x824) = (u8*)self + 0xE30;
    M2C_FIELD(self, void**, 0x828) = (u8*)self + 0xE40;
    M2C_FIELD(self, void**, 0x82C) = (u8*)self + 0xE70;
    M2C_FIELD(self, void**, 0x830) = (u8*)self + 0xE84;
    M2C_FIELD(self, void**, 0x834) = (u8*)self + 0xE90;
    M2C_FIELD(self, void**, 0x838) = (u8*)self + 0xE9C;
    M2C_FIELD(self, void**, 0x83C) = (u8*)self + 0xEB0;
    entry = firstEntry;
    remaining = 0x49;
    do {
        component = *entry;
        remaining -= 1;
        entry++;
        vtable = M2C_FIELD(component, void**, 4);
        M2C_FIELD(vtable, void (**)(void*, void*), 0xC)((void*)(((s8*)component) + M2C_FIELD(vtable, s16*, 8)),
                                                        M2C_FIELD(self, void**, 0x714));
    } while (remaining >= 0);
}
#ifdef NON_MATCHING
// Unmatched: loop iterator lifetimes and register scheduling.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_181028", func_00181348);
#endif
