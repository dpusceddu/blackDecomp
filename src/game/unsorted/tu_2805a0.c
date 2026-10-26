#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00282C18(void *);

typedef struct {
    u8 unk_00[0x18];
    s16 adjustment;
    u16 unk_1A;
    void (*update)(void *, f32);
} Recovered_ListenerVtable;

typedef struct {
    u8 unk_00[0x60];
    Recovered_ListenerVtable *vtable;
} Recovered_Listener;

typedef struct {
    Recovered_Listener *listeners[2];
    u32 count;
} Recovered_ListenerCollection; /* Layout and callback role UNVERIFIED. */

#ifdef NON_MATCHING
// Unmatched: callback loop register allocation and scheduling differ.
void func_002805A0(Recovered_ListenerCollection *self, f32 delta) {
    u32 index = 0;
    Recovered_Listener **cursor = self->listeners;
    while (index < self->count) {
        Recovered_Listener *listener = *cursor++;
        Recovered_ListenerVtable *vtable = listener->vtable;
        index++;
        vtable->update((u8 *)listener + vtable->adjustment, delta);
    }
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0", func_002805A0);

void func_00280628(Recovered_ListenerCollection *self) {
    u32 index = 0;
    Recovered_Listener **cursor = self->listeners;
    do {
        Recovered_Listener *listener = *cursor;
        index++;
        if (listener != 0) {
            func_00282C18(listener);
            *cursor = 0;
        }
        cursor++;
    } while (index < 2);
}

s32 func_00280680(s32 arg0, s32 arg1)
{
  s8 *new_var;
  new_var = (s8 *) (arg0 + (arg1 * 4));
  return *((s32 *) (new_var + 0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0", func_00280690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2805a0", func_00280698);
