// Declarations of the Kynapse source module "callbacks" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_CALLBACKS_HPP
#define BLACK_KYNAPSE_MODULE_CALLBACKS_HPP
#include "kynapse/compat.hpp"

// Callback registries, entry comparators and id validity checks.

#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);
void* Kaim_AllocateTagged(unsigned int size, const void* tag);
extern const unsigned char gTextTag;

struct Callback;

typedef void (*CallbackFunction)(void* subject, void* context);

extern int gFirstCount;
extern CallbackFunction* gFirstFunctions;
extern void** gFirstContexts;

// 0x2b8198 (count), 0x2b81a0 (functions), 0x2b81a4 (contexts).
extern int gSecondCount;
extern CallbackFunction* gSecondFunctions;
extern void** gSecondContexts;

extern int gFirstCapacity;
extern int gSecondCapacity;


// Unmatched: the original copies the entries with strength-reduced pointers and sizes the arrays from
// the doubled capacity; moving doubling before the size read did not improve it (371 vs 363 bytes).
// Appends a callback to the first registry, growing both arrays (16 entries first, then doubling).
void __stdcall Kaim_AddFirstCallback(CallbackFunction function, void* context);



// Unmatched: original strength-reduces both array cursors and preserves the function base; cached bases, loop forms and count snapshots (24 variants) gave no improvement (51 bytes).
void __stdcall Kaim_RemoveFirstCallback(CallbackFunction function, void* context);



// Unmatched: as Kaim_AddFirstCallback.
// Appends a callback to the second registry.
void __stdcall Kaim_AddSecondCallback(CallbackFunction function, void* context);



// Unmatched: same strength-reduced cursor/base issue as RemoveFirstCallback (51 bytes).
void __stdcall Kaim_RemoveSecondCallback(CallbackFunction function, void* context);


struct SortEntry {
    int id;       // 0x00 (-1 marks an unused entry)
    float weight;
    float scale;
    float bias;
    int unknown10;
};

struct SortTable {
    unsigned char unknown00[0x0c];
    unsigned int count;
    unsigned char unknown10[8];
    SortEntry* entries;

    SortEntry* Get(unsigned int index)
    {
        if (index >= count)
            return 0;
        SortEntry* entry = &entries[index];
        return entry->id == -1 ? 0 : entry;
    }
};

extern SortTable* gSortTable;


int Kaim_CompareByWeight(const unsigned int* a, const unsigned int* b);



int Kaim_CompareByScale(const unsigned int* a, const unsigned int* b);



int Kaim_CompareByBias(const unsigned int* a, const unsigned int* b);


extern int gId0;
extern int gId1;
extern int gId2;
extern int gId3;
extern int gId4;
extern int gId5;
extern int gId6;
extern int gId7;
extern int gId8;
extern int gId9;
extern int gId10;
extern int gId11;
extern int gId12;
extern int gId13;
extern int gId14;
extern int gId15;


bool Kaim_AllRegisteredIdsValid();


#endif
