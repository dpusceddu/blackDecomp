#ifndef KYNAPSE_GRAPH_INDEX_H
#define KYNAPSE_GRAPH_INDEX_H

/* Partial views; graph roles, record contents and full extents are UNVERIFIED. */
typedef struct Recovered_KynapseGraphRecord {
    int value;
    char unk_04[16];
} Recovered_KynapseGraphRecord;
typedef struct Recovered_KynapseGraphIndexOwner Recovered_KynapseGraphIndexOwner;
typedef struct Recovered_KynapseGraphIterator {
    int index;
    Recovered_KynapseGraphIndexOwner* owner;
} Recovered_KynapseGraphIterator;
struct Recovered_KynapseGraphIndexOwner {
    char unk_00[0x18];
    Recovered_KynapseGraphRecord* records;
    char unk_1c[0x1c];
    int* firstIndices;
    int* secondIndices;
    char unk_40[0x1c];
    Recovered_KynapseGraphIterator end;
    Recovered_KynapseGraphRecord firstDefault;
    Recovered_KynapseGraphRecord secondDefault;
};
#endif
