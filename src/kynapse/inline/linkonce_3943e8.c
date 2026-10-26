#include "include_asm.h"
#include "ps2/prelude.h"

/* Partial views; object identities and complete extents are UNVERIFIED. */
typedef struct {
    char unknown[8];
    short adjustment;
    short unk_0a;
    void (*destroy)(void*, int);
} Recovered_KynapseArrayElementTable;
typedef struct Recovered_KynapseArrayElement {
    Recovered_KynapseArrayElementTable* table;
    char unknown[0x30];
} Recovered_KynapseArrayElement;
typedef struct {
    void* table;
    Recovered_KynapseArrayElement* elements;
    char unknown[0x10];
    int unk_18;
} Recovered_KynapseArrayOwner;
extern int D_003F0948, D_003E0040;
extern void (*D_003C87E0)(void*);
void func_003943E8(Recovered_KynapseArrayOwner* self, int flags) {
    self->table = &D_003F0948;
    if (self->unk_18 && self->elements) {
        Recovered_KynapseArrayElement* element = self->elements + *(int*)((char*)self->elements - 16);
        while (self->elements != element) {
            Recovered_KynapseArrayElementTable* table;
            --element;
            table = element->table;
            table->destroy((char*)element + table->adjustment, 0);
        }
        D_003C87E0((char*)self->elements - 16);
    }
    self->table = &D_003E0040;
    if (flags & 1) D_003C87E0(self);
}
