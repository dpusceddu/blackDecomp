// Declarations of the Kynapse source module "label" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_LABEL_HPP
#define BLACK_KYNAPSE_MODULE_LABEL_HPP
#include "kynapse/compat.hpp"

// Label: a named record holding an array of 0x58-byte placement records, and the record class.
#include "kynapse/alloc.hpp"
#include "kynapse/data_io.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);

extern void (*memoryRelease)(void*);

struct Vec3 {
    float x, y, z;
};
extern Vec3 gOrigin;
extern const char* gDefaultName;
extern const char* gDefaultTag;
extern const char* gDefaultLabel;
extern const char* gActionNames[5];    // 0x297e38 (idle, then the four movement modes)

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int, void* place) { return place; }
    static void operator delete(void* block) { memoryRelease(block); }
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
    static void operator delete[](void* block) { memoryRelease(block); }
};

// Record with a position and two fixed-size text buffers.
struct Record : ObjectBase {
    Vec3 position;
    char name[8];
    char tag[0x40];

    Record();
    Record& operator=(const Record& other);
    virtual ~Record();                 // vector deleting destructor at 0x4e9d0
};







struct Label : ObjectBase {
    Record* records;                   // 0x04 (array)
    int field08;
    char changed;
    char text[0x103];
    int field110;

    Label();
    virtual ~Label();                  // 0x4e940, deleting destructor 0x4e9b0
    virtual void Moved(unsigned int from, unsigned int to) {}   // slot 1
    void SetChanged(char value);
    bool Insert(const Record& record, unsigned int index);
    bool Load(const void* resource);
};







Label* MakeLabel(void* place);


Record* MakeRecords(unsigned int count);



// Unmatched: transcribed from the disassembly.
// Inserts a record at `index` (-2 appends), growing the array by five records when it is full.



// Unmatched: EBX zero already reproduced; record/string temporary lifetimes and 0x90 vs 0xbc frame differ.
// Reads a Kynogon Path Way label and movement-command stream, then fills its trailing text fields.


#endif
