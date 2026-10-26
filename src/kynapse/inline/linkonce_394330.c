#include "include_asm.h"
#include "ps2/prelude.h"

extern int D_003E0040;
extern void (*D_003C87E0)(void*);

/* Partial view; the object type and full extent are UNVERIFIED. */
typedef struct Recovered_KynapseResetPair {
    void* unk_00;
    void* unk_04;
} Recovered_KynapseResetPair;

void func_00394330(Recovered_KynapseResetPair* self, int flags) {
    self->unk_04 = &D_003E0040;
    self->unk_00 = &D_003E0040;
    if (flags & 1) D_003C87E0(self);
}
