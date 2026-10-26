#include "include_asm.h"
#include "ps2/prelude.h"

/* Partial views; the object type, callback purpose and full extents are UNVERIFIED. */
typedef struct Recovered_KynapseCallbackTable {
    unsigned char unk_00[40];
    short unk_28;
    short unk_2a; /* UNVERIFIED: unused in this function. */
    void (*unk_2c)(void*);
} Recovered_KynapseCallbackTable;

typedef struct Recovered_KynapseCallbackObject {
    Recovered_KynapseCallbackTable* unk_00;
    unsigned char unk_04[68];
    unsigned int unk_48;
} Recovered_KynapseCallbackObject;

int func_00394C20(Recovered_KynapseCallbackObject* self) {
    Recovered_KynapseCallbackTable* table = self->unk_00;
    table->unk_2c((char*)self + table->unk_28);
    return self->unk_48 == ~0u;
}
