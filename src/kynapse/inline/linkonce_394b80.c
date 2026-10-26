#include "include_asm.h"
#include "ps2/prelude.h"

extern int D_003E0040;
extern void (*D_003C87E0)(void*);

/* Partial view; the object type and full extent are UNVERIFIED. */
typedef struct Recovered_KynapseCleanupView {
    void* unk_00;
    unsigned char unk_04[12];
    int unk_10;
} Recovered_KynapseCleanupView;

void func_00394B80(Recovered_KynapseCleanupView* self, int flags) {
    self->unk_00 = &D_003E0040;
    self->unk_10 = 0;
    if (flags & 1) D_003C87E0(self);
}
