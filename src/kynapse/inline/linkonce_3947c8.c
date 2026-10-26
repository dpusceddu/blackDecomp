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
    char unknown[0x24];
} Recovered_KynapseArrayElement;
typedef struct {
    void* table;
    Recovered_KynapseArrayElement* elements;
    char unknown[0x10];
    int unk_18;
} Recovered_KynapseArrayOwner;
extern int D_003F0F18, D_003E0040;
extern void (*D_003C87E0)(void*);
void func_003947C8(Recovered_KynapseArrayOwner* self, int flags) {
    self->table = &D_003F0F18;
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
/* Partial owner view; its identity and complete extent are UNVERIFIED. */
typedef struct Recovered_KynapseChildOwner {
    void* table;
    Recovered_KynapseArrayElement* child;
} Recovered_KynapseChildOwner;

extern int D_003F0F00;

void func_003948A0(Recovered_KynapseChildOwner* self, int flags) {
    self->table = &D_003F0F00;
    if (self->child) {
        Recovered_KynapseArrayElement* child = self->child;
        Recovered_KynapseArrayElementTable* table = child->table;
        table->destroy((char*)child + table->adjustment, 3);
    }
    self->table = &D_003E0040;
    if (flags & 1) D_003C87E0(self);
}
