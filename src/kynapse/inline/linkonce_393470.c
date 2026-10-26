#include "include_asm.h"
#include "ps2/prelude.h"
#include "kynapse/graph_index.h"

/* Partial visitor view; field roles and complete extent are UNVERIFIED. */
typedef struct {
    char unk_00[0x14];
    unsigned char* states;
    short* selected;
    short count;
} Recovered_KynapseGraphStateVisitor;
static inline Recovered_KynapseGraphRecord* First(Recovered_KynapseGraphIterator* it) {
    Recovered_KynapseGraphIndexOwner* owner = it->owner;
    if (it == &owner->end) return &owner->firstDefault;
    return &owner->records[owner->firstIndices[it->index]];
}
static inline Recovered_KynapseGraphRecord* Second(Recovered_KynapseGraphIterator* it) {
    Recovered_KynapseGraphIndexOwner* owner = it->owner;
    if (it == &owner->end) return &owner->secondDefault;
    return &owner->records[owner->secondIndices[it->index]];
}
static inline int IteratorIndex(const Recovered_KynapseGraphIterator* it) { return it->index; }
int func_00393470(Recovered_KynapseGraphStateVisitor* visitor, Recovered_KynapseGraphIterator* it) {
    Recovered_KynapseGraphRecord* first = First(it);
    Recovered_KynapseGraphRecord* second = Second(it);
    int secondIndex = second->value;
    if (visitor->states[secondIndex] == 1 && visitor->states[first->value] == 0) {
        visitor->selected[visitor->count] = IteratorIndex(it);
        ++visitor->count;
    }
    return 1;
}
