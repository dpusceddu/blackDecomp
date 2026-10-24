// Declarations of the Kynapse source module "grid" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_GRID_HPP
#define BLACK_KYNAPSE_MODULE_GRID_HPP
#include "kynapse/compat.hpp"

// A grid of flags and values allocated from the sizes of a source description.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

struct Vec3 {
    float x, y, z;
};
extern Vec3 gOrigin;

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void operator delete(void* block) { memoryRelease(block); }
    static void* operator new(unsigned int, void* place) { return place; }
};

struct GridSource {
    unsigned char unknown00[0x14];
    unsigned int flagCount;
    unsigned char unknown18[0x18];
    unsigned int valueCount;
};

struct GridCell {
    unsigned int index;
    Vec3 position;
};

int Kaim_TestPoints(const Vec3* a, const Vec3* b, int mode, int flag);

struct Grid : ObjectBase {
    Vec3 origin;
    int unknown10;
    char* flags;
    short* values;
    short count;

    Grid();
    virtual ~Grid();                 // deleting destructor 0x5dc20
    void AllocateFlags(const GridSource* source);
    bool Classify(GridCell* cell);
    void AllocateValues(const GridSource* source);
};











Grid* MakeGrid(void* place);


#endif
