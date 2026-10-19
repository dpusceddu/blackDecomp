#ifndef BLACK_PARAMETER_TABLES_HPP
#define BLACK_PARAMETER_TABLES_HPP
#include "kynapse/alloc.hpp"

// Recovered parameter-table names; PS2 offsets and sizes verified by the constructors,
// destructor and Update in parameter_tables_manual.cpp. Each slot has a 24-byte BufferSet.
extern void (*memoryRelease)(void*);

extern unsigned int gTableSizeA;
extern unsigned int gTableSizeB;
extern unsigned int gTableSizeC;

extern void (*gPreUpdateHook)();
extern float (*gFloatHook)();
const float kDefaultFloat = 0.0f;
extern const float kUnlimited;
extern float gSavedFloat;
extern float gUpdateZero;
extern float gUpdateStep;
extern float gElapsed;
extern int (*gCompare)(const void*, const void*);
extern int gSelected;

inline float Kaim_QueryFloat()
{
    if (gFloatHook)
        return gFloatHook();
    return kDefaultFloat;
}

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
    static void operator delete[](void* block) { memoryRelease(block); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Slot {
    unsigned char unknown0[0x10];
    unsigned char active;
    unsigned char unknown11[3];
};
struct SlotTable {
    unsigned char unknown00[4];
    Slot* slots;
    unsigned char unknown08[0x10];
    unsigned int capacity;
};
#include "ps2/kynapse/parameter_slots.hpp"

struct SlotUser {
    unsigned char unknown00[0x14];
    Slot* slot;
    int GetIndex() const;
};
struct BufferSet : ObjectBase {
    float* sums;          // 0x04, per-name accumulated cost
    float total;          // 0x08
    float weight;         // 0x0c
    float* values;        // 0x10 in BufferSet; 0x08 in IndexTable
    float* ranks;         // 0x14

    BufferSet();
    virtual ~BufferSet();
};
struct IndexTable : ObjectBase {
    unsigned int* indices;
    float* values;        // 0x10 in BufferSet; 0x08 in IndexTable

    IndexTable();
    virtual ~IndexTable();
};


struct ParameterTables : ObjectBase {
    unsigned int countB;
    unsigned int countA;
    unsigned int countC;
    float* b10;
    float* a14;
    float* c18;
    float threshold;
    float* a20;
    int* a24;
    float* a28;
    float* b2c;
    float* c30;
    BufferSet* sets;
    IndexTable* indexTables;
    float* a3c;
    float* a40;
    int* a44;
    int* order;
    int selected;
    unsigned char fired;

    ParameterTables();
    virtual ~ParameterTables();
    bool ConsumeList(int index, struct IndexUser* user);
    void Update(float step);
    bool Raise(int index, SlotUser* user);
    void Store(int index, SlotUser* user);
    bool Consume(int index, SlotUser* user);
    void Accumulate(int index, SlotUser* user);
    float Remaining(int index);
    int NextSlot();
};

ParameterTables* GetNameTables();


int CompareSets(const void*,const void*);

struct SlotLink { unsigned int unknown; SlotUser* user; unsigned int unknown8; SlotLink* next; };
struct SlotLinks { unsigned int unknown[2]; SlotLink* first; };
// Inferred iterator used by the guarded list-consuming method.
struct SlotCursor : ObjectBase {
    SlotLink* current;
    SlotCursor(SlotLinks* links) : current(links->first) {}
};
struct IndexUser { unsigned int unknown[2]; SlotLinks* slots; int GetIndex() const; };
typedef char VerifiedBufferSetSize[sizeof(BufferSet) == 0x18 ? 1 : -1];
typedef char VerifiedIndexTableSize[sizeof(IndexTable) == 0x0c ? 1 : -1];
typedef char VerifiedParameterTablesSize[sizeof(ParameterTables) == 0x54 ? 1 : -1];
#endif
