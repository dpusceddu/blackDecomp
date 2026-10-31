#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8", func_001A24B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8", func_001A2500);

s32 func_001A2580(void) {
    return 1;
}

void func_001A2588(void) {

}

#ifdef NON_MATCHING
// Unmatched: state-method pointer and callback register allocation differ (4 instructions).
typedef struct ModeStateMethod {
    s16 adjustment;
    u16 reserved;
    void (*call)(void*, s32);
} ModeStateMethod;
typedef struct ModeStartMethods {
    u8 unknown[0x40];
    ModeStateMethod setState;
} ModeStartMethods;
/* Accessed native fields; original class identity and total size are UNVERIFIED. */
typedef struct ModeStartView {
    u8 unknown[0x35];
    u8 enabled, pending, unknown37;
    void* owner;
    s32 index;
    u8 unknown40[0x10];
    s32 counter, phase;
    u8 unknown58[8];
    ModeStartMethods* methods;
} ModeStartView;
extern void* D_0040F4E0;
extern s32 func_0015D2A8(void*, s32);
extern void func_001A2968(void*);
extern void func_001A2B70(void*);
void func_001A2590(ModeStartView* self) {
    ModeStartMethods* methods;
    self->enabled = 1;
    self->pending = 0;
    self->counter = 0;
    self->index = func_0015D2A8(D_0040F4E0, *M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s8**, 0x2A4));
    func_001A2968(self);
    func_001A2B70(self);
    methods = self->methods;
    self->phase = 0;
    methods->setState.call((u8*)self + methods->setState.adjustment, 0);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8", func_001A2590);
#endif
