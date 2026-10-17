// Declarations of the Kynapse source module "buffers3" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_BUFFERS3_HPP
#define BLACK_KYNAPSE_MODULE_BUFFERS3_HPP
#include "kynapse/compat.hpp"

// A bound object that owns three buffers.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct BufferOwner {
    unsigned char unknown00[0x14];
    int handle;
};

struct BoundBase : ObjectBase {
    BufferOwner* owner;
    BoundBase(BufferOwner* bound) : owner(bound) {}
};

struct BoundBuffers : BoundBase {
    int handle;
    void* first;
    void* second;
    void* third;
    int count;

    BoundBuffers(BufferOwner* bound);
    virtual ~BoundBuffers();           // deleting destructor at 0x55d60
};






ObjectBase* CreateBoundBuffers(BufferOwner* bound);


#endif
