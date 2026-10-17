// Declarations of the Kynapse source module "leaf_functions" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_LEAF_FUNCTIONS_HPP
#define BLACK_KYNAPSE_MODULE_LEAF_FUNCTIONS_HPP
#include "kynapse/compat.hpp"

// Kynapse leaf functions and small classes, one batch in original address order.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

extern int gIdA;
extern int gIdB;
extern int gIdC;
extern int gIdD;
extern int gIdE;
extern int gIdF;
extern int gIdG;


bool Kaim_AllIdsValid();


struct NamedObject {
    unsigned char unknown00[0x10];
    const char* name;

    const char* GetName() const;
};


bool __stdcall Kaim_IsHiddenName(const NamedObject* object);


struct ItemList {
    unsigned char unknown00[8];
    unsigned int count;
};

struct Cursor {
    unsigned char unknown00[0x38];
    ItemList* list;
    unsigned int index;
    bool flag40;
    bool flag41;
    bool wrap;
    bool flag43;
    unsigned char unknown44[4];
    bool flag48;
    unsigned char unknown49[7];
    bool flag50;

    void Wrap();
};



struct Vec3 {
    float x, y, z;
};


bool Kaim_Vec3Equal(const Vec3* a, const Vec3* b);



void* Kaim_Allocate(unsigned int size);


struct ObjectRoot {
    virtual ~ObjectRoot() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

// Base with eight cleared fields.
struct ZeroedBase : ObjectRoot {
    int field04, field08, field0c, field10, field14, field18, field1c, field20;

    ZeroedBase();
    virtual ~ZeroedBase();
};

// Controller whose position data is copied from a 4-component vector.
struct VectorController : ZeroedBase {
    int axisX, axisY, axisZ;
    int component0;
    int extra;

    VectorController(const int* source, int value);
    virtual ~VectorController();
};



VectorController* MakeVectorController(const int* source, int value);


#endif
