#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_108db8", func_00108DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_108db8", func_00108E68);
#ifdef NON_MATCHING
// Unmatched: scan and branch scheduling differ.
// Partial request queue views; flag meanings are UNVERIFIED.
typedef struct {
    char unknown00[0x138];
    u8 active, pending, unknown13a, finish;
    char unknown13c[4];
} AudioSlotDraft;
typedef struct {
    AudioSlotDraft slots[10];
} AudioQueueDraft;
extern void func_00109180(AudioSlotDraft*);
extern void func_00109278();
extern void func_00108F28(AudioSlotDraft*);

s32 func_00108E78(AudioQueueDraft* self) {
    s32 i = 0, found;
    AudioSlotDraft* slot = self->slots;
    while ((found = i < 10)) {
        if (slot->active) {
            if (i == 8 && self->slots[9].pending)
                func_00109180(&self->slots[9]);
            else
                func_00108F28(slot);
            break;
        }
        if (slot->pending) {
            func_00109180(slot);
            break;
        }
        if (slot->finish) {
            func_00109278(slot);
            break;
        }
        slot++;
        i++;
    }
    return found;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_108db8", func_00108E78);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_108db8", func_00108F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_108db8", func_00109180);
// Partial audio request view; original type and flag meanings are UNVERIFIED.
typedef struct AudioRequestView AudioRequestView;
struct AudioRequestView {
    s32 unknown00, handle;
    char unknown08[0x10c];
    void (*callback)(AudioRequestView*, s32);
    s32 callbackArg;
    char unknown11c[0x1e];
    u8 field13a, field13b;
};
extern void* func_003249E8(s32);
extern void func_00271480(void);
extern s32 func_00324D98(s32, s32);

void func_00109278(AudioRequestView* self) {
    if (self->handle) {
        func_003249E8(self->handle);
        while (!func_00324D98(self->handle, 0)) func_00271480();
        self->handle = 0;
    }
    self->field13a = 0;
    self->field13b = 0;
    if (self->callback) self->callback(self, self->callbackArg);
}
