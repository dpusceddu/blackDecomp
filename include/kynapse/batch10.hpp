// Declarations of the Kynapse source module "batch10" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_BATCH10_HPP
#define BLACK_KYNAPSE_MODULE_BATCH10_HPP
#include "kynapse/compat.hpp"

// Assorted methods: a byte grid lookup, a named record, a type registry search, a cache of
// per-type objects and two small initialisers.

#pragma function(memcpy)

struct ClassInfo { unsigned char unknown00[0x10c]; ClassInfo* parent; };

struct Component {
    virtual ~Component();
    virtual void Slot1();
    virtual ClassInfo* GetClassInfo();     // slot 2
};

// A grid of bytes (0xff marks an unset cell) scaled into a float.
struct ByteGrid {
    unsigned char unknown00[8];
    unsigned char* cells;
    int stride;
    float scale;
};

struct GridHolder {
    virtual void Slot0();
    ByteGrid* grid;
    virtual bool Sample(int unused, const int* x, const int* y, float* out);
};



// A record holding a 0x80-byte name, an id and a flag.
struct NamedRecord {
    virtual ~NamedRecord();
    char name[0x80];
    int id;
    bool flag;
    unsigned char unknown89[0x83];
    int count;

    NamedRecord(const char* source, int newId, bool newFlag);
};



// The registry of typed entries, each holding the components of one type.
struct TypeEntry {
    unsigned char unknown00[0x84];
    int typeId;
    unsigned char unknown88[4];
    Component* components[32];
    unsigned int componentCount;
};

struct TypeRegistry {
    unsigned char unknown00[4];
    TypeEntry** entries;
    unsigned int count;

    Component* Find(int typeId, ClassInfo* wanted);
};



struct SlotEntry { int id; int value; };

struct SlotSet {
    unsigned char unknown00[0x28];
    unsigned int capacity;
    unsigned char unknown2c[4];
    unsigned int count;
    SlotEntry* entries;
};

struct Visitor {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Begin(SlotSet* set);      // slot 2
    virtual void Slot3();
    virtual bool Accept(SlotEntry* entry); // slot 4

    bool VisitAll(SlotSet* set);
};



// A cache of one object per type, created and initialised on first use.
struct Creatable {
    virtual ~Creatable();
    virtual void Slot1();
    virtual void Init(int argument);       // slot 2
};

struct TypeInfo {
    // PS2: index and factory are at +0 and +4 (verified by CreatableCache::Select).
    int id;
    Creatable* (*create)();
};
typedef char VerifiedTypeInfoSize[sizeof(TypeInfo) == 8 ? 1 : -1];

struct CreatableCache {
    unsigned char unknown00[0x18];
    Creatable** slots;
    Creatable* current;
    unsigned char unknown20[0x44];
    int argument;

    void Select(TypeInfo* type);
};



// Looks up the service component of the engine's type registry class.
struct TypeRegistryHolder;
struct EngineObject {
    TypeRegistry* FindByClass(ClassInfo* wanted);
    unsigned char unknown00[0xc];
    float frameTime;
};
extern EngineObject* gEngine;
extern ClassInfo gTypeRegistryClass;
extern ClassInfo gProviderClass;
extern const float kDefaultFloat;

struct ProviderUser {
    unsigned char unknown00[4];
    Component* provider;

    void Init(int argument);
};



struct Pacer {
    virtual ~Pacer();
    unsigned char unknown04[0x140];
    int unknown144;
    int unknown148;
    float shortInterval;
    float longInterval;

    Pacer();
};



#endif
