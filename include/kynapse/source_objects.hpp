// Declarations of the Kynapse source module "source_objects" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SOURCE_OBJECTS_HPP
#define BLACK_KYNAPSE_MODULE_SOURCE_OBJECTS_HPP
#include "kynapse/compat.hpp"

// Objects built from a source description: a record made by a factory and a square table.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

namespace Kaim {

struct ObjectRoot {
    virtual ~ObjectRoot() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Description {
    unsigned char unknown00[0x14];
    unsigned int size;
};

struct ObjectWithSource : ObjectRoot {
    Description* source;
    ObjectWithSource(Description* newSource) : source(newSource) {}
};

struct SourceRecord : ObjectWithSource {
    unsigned int size;
    int unknown0c;
    int unknown10;
    SourceRecord(Description* newSource)
        : ObjectWithSource(newSource), size(newSource->size), unknown0c(0), unknown10(0) {}
    virtual ~SourceRecord();
};


SourceRecord* Kaim_MakeSourceRecord(Description* source);


// A table of size * size bytes (vtable 0x2851cc).
struct SquareTable : ObjectWithSource {
    unsigned char* cells;
    unsigned int size;
    int unknown10;
    int unknown14;
    SquareTable(Description* newSource);
    virtual ~SquareTable();
};



}  // namespace Kaim

#endif
