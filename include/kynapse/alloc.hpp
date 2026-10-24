// Ported from an unpublished companion project.
#ifndef BLACK_KYNAPSE_ALLOC_HPP
#include "kynapse/compat.hpp"
#define BLACK_KYNAPSE_ALLOC_HPP

// Kynapse allocation service: an allocator object whose sixth slot allocates a block (written
// through `out`, with a tag returned) and an optional hook told about every allocation.
struct KaimAllocator {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual unsigned int Allocate(unsigned int size, void** out);  // slot 5
};
extern KaimAllocator* gKaimAllocator;
extern void (*gKaimAllocateHook)(void* block, unsigned int size, unsigned int tag);

inline void* KaimAllocate(unsigned int size)
{
    void* block = 0;
    unsigned int tag = gKaimAllocator->Allocate(size, &block);
    if (gKaimAllocateHook)
        gKaimAllocateHook(block, size, tag);
    return block;
}

#endif
