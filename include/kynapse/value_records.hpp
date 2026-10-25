// Declarations of the Kynapse source module "value_records" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_VALUE_RECORDS_HPP
#define BLACK_KYNAPSE_MODULE_VALUE_RECORDS_HPP
#include "kynapse/compat.hpp"

// Small Kynapse helpers (seventh batch): value records, pair tables and trivial constructors.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int, void* place) { return place; }
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
    static void operator delete[](void* block) { memoryRelease(block); }
    static void operator delete(void* block) { memoryRelease(block); }
};

// Five-value record.
struct QuintRecord : ObjectBase {
    int first, second, third, fourth, fifth;     // 0x04..0x14
    QuintRecord(int a, int b, int c, int d, int e)
    {
        first = a;
        second = b;
        third = c;
        fourth = d;
        fifth = e;
    }
};
QuintRecord* MakeQuint(int a, int b, int c, int d, int e, void* place);


struct ScoreKey {
    unsigned char unknown00[8];
    int major;
    int minor;
};


int Kaim_CompareScoreKeys(const ScoreKey* a, const ScoreKey* b);


struct NineSlots {
    int slot[8];                                 // 0x04..0x20 (after the vptr)
};

struct Elem16 : ObjectBase {
    int a, b, c;
};
Elem16* MakeElem16Array(unsigned int count);
   // vector deleting destructor at 0x64200

extern float* gPairValues;
extern unsigned char* gPairFlags;


float __stdcall Kaim_GetPairValue(int a, int b);



// Unmatched: register assignment of the table base and index differs.
unsigned char __stdcall Kaim_GetPairFlag(int a, int b);


struct ResetCounters {
    int unknown00;
    int a, b, c;                                 // 0x04, 0x08, 0x0c
    int unknown10;
    int d, e, f;                                 // 0x14, 0x18, 0x1c
    int g;

    void Reset();
};



struct Cursor94 {
    unsigned char unknown00[0x94];
    int position;
    void Rewind();
};


#endif
