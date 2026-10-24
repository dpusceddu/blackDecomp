// Declarations of the Kynapse source module "pair_owner" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_PAIR_OWNER_HPP
#define BLACK_KYNAPSE_MODULE_PAIR_OWNER_HPP
#include "kynapse/compat.hpp"

// Owner of the shared pair tables: instances count themselves; the last one frees the tables
// and removes its callback.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);
extern "C" double __cdecl atof(const char*);

namespace Kaim {
struct ChildBuffers {
    const char* GetSecond() const;
    const char* GetValue() const;
};
}
using Kaim::ChildBuffers;

extern void (*memoryRelease)(void*);

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Tagged : ObjectBase {
    int tag;
    Tagged(int value);
};

struct EntityObject;
int Entity_ApplyD(EntityObject* entity, int first, int second);
extern EntityObject* gEngine;

struct PairOwner;
void PairOwnerOnRemoved(PairOwner*, void*);

extern int gPairOwnerCount;
extern void* gPairFlagsTable;
extern void* gPairSecondTable;
extern void* gPairThirdTable;
extern void* gPairValuesTable;

struct Element : ObjectBase {
    float coneExpiry, pairExpiry, distance;
    bool inCone, blocked, heard, otherGroup;
    static void operator delete[](void* block) { memoryRelease(block); }
};
typedef char assert_PairOwnerElement_size[(sizeof(Element) == 0x14) ? 1 : -1];

struct PairOwnerBase : Tagged {
    float low;
    float high;
    unsigned char unknown10[8];
    int field18, field1c, field20, field24, field28, field2c;   // 0x18..0x2c
    Element* elements;                 // 0x30 (array)
    int field34, field38, field3c, field40, field44;            // 0x34..0x44

    PairOwnerBase(int value) : Tagged(value)
    {
        elements = 0;
        field18 = 0;
        field1c = 0;
        field20 = 0;
        field24 = 0;
        field28 = 0;
        field2c = 0;
        field34 = 0;
        field38 = 0;
        field40 = 0;
        field44 = 0;
        field3c = 0;
        tag = value;
    }
};

struct PairOwner : PairOwnerBase {
    PairOwner(int value);
    bool Configure(ChildBuffers* config);
    virtual __declspec(noinline) ~PairOwner();   // Ghidra /default.xbe 0x68030 (deleting 0x68330)
};

#endif
