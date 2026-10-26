#ifndef KYNAPSE_ARRAY_CLEANUP_H
#define KYNAPSE_ARRAY_CLEANUP_H

/* Partial views; object identities and complete extents are UNVERIFIED. */
typedef struct Recovered_KynapseSmallElementTable {
    char unk_00[8];
    short adjustment;
    short unk_0a;
    void (*destroy)(void*, int);
} Recovered_KynapseSmallElementTable;

typedef struct Recovered_KynapseSmallElement {
    Recovered_KynapseSmallElementTable* table;
    char unk_04[0x10];
} Recovered_KynapseSmallElement;

typedef struct Recovered_KynapseSmallArrayOwner {
    void* table;
    Recovered_KynapseSmallElement* elements;
    char unk_08[0x10];
    int unk_18;
} Recovered_KynapseSmallArrayOwner;

#ifdef __cplusplus
extern "C" {
#endif
extern int D_003E0040;
extern void (*D_003C87E0)(void*);
#ifdef __cplusplus
}
#endif

static inline void KynapseSmallArray_Destroy(Recovered_KynapseSmallArrayOwner* self, int flags, void* initialTable) {
    self->table = initialTable;
    if (self->unk_18 && self->elements) {
        Recovered_KynapseSmallElement* element = self->elements + *(int*)((char*)self->elements - 16);
        while (self->elements != element) {
            Recovered_KynapseSmallElementTable* table;
            --element;
            table = element->table;
            table->destroy((char*)element + table->adjustment, 0);
        }
        D_003C87E0((char*)self->elements - 16);
    }
    self->table = &D_003E0040;
    if (flags & 1) D_003C87E0(self);
}
#endif
