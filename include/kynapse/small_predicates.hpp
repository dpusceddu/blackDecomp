// Declarations of the Kynapse source module "small_predicates" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SMALL_PREDICATES_HPP
#define BLACK_KYNAPSE_MODULE_SMALL_PREDICATES_HPP
#include "kynapse/compat.hpp"

// Assorted small functions: predicates, lookups, thin wrappers and float tests.

extern bool (*gHook297F44)(const float*, const float*, float, void*, int);
extern float (*gFloatHook)();
extern const float kDefaultFloat;
extern float gSavedFloat;

struct Slot { unsigned char unknown0[0x14]; };

struct SlotUser {
    unsigned char unknown00[0x14];
    Slot* slot;
    int GetIndex() const;
};

// Both halves present in exactly one of each pair of pointers.
struct PairedPointers {
    unsigned char unknown00[0x18];
    void* a;
    void* b;
    unsigned char unknown20[8];
    void* c;
    void* d;

    bool ExactlyOne();
};



struct Member { unsigned char unknown00[0x84]; int id; };   // id at 0x84

struct MemberList {
    unsigned char unknown00[4];
    Member** items;
    unsigned int count;

    bool Contains(int id);
};



struct Point4 { int unknown0; float v1, v2, v3; };

struct Measure {
    virtual void Slot0();
    virtual bool Distance(int unused, const Point4* a, const Point4* b, float* out);
};



struct Row { unsigned char unknown00[0x14]; float* values; };   // stride 0x18
struct Rows {
    unsigned char unknown00[4];
    unsigned int count;
    unsigned char unknown08[0x2c];
    Row* rows;
    void Store(int index, SlotUser* user);
};
struct SlotOwner {
    unsigned char unknown00[0x10];
    unsigned int slotCount;
};
extern SlotOwner* gSlotOwner;



struct Latch {
    unsigned char unknown00[0x1c];
    float threshold;
    unsigned char unknown20[0x30];
    bool fired;

    void Check();
};



bool Kaim_TestSegment(const float* from, const float* to, void* actor, int mode, float radius);


struct Motion {
    unsigned char unknown00[0x28];
    float maxSpeed;
    unsigned char unknown2c[0xc];
    float maxVertical;
    unsigned char unknown3c[0x88];
    float x;
    float y;
    float z;
};


bool WithinSpeed(const Motion* m);


#endif
