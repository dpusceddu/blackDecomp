#include "include_asm.h"

#include "kynapse/graph/allocators.hpp"
namespace Kaim {

CBaseAllocator::~CBaseAllocator() { delete children; }
CAllocator::~CAllocator() {}
CPoolBasedAllocator::~CPoolBasedAllocator() {
    if(owner)((CAllocator*)owner)->Release((unsigned int)buffer);
    if(next)next->Remove(this);
}
}

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
void *CPoolBasedAllocator::GetBlock(unsigned int count) {
    if(!count)count=1;
    int n=ValidAlignment();unsigned int mask;const int *padding;
    extern const int Padding2[] __asm__("D_004068F0");extern const int Padding4[] __asm__("D_004068F8");extern const int Padding8[] __asm__("D_00406908");extern const int Padding16[] __asm__("D_00406928");extern const int Padding32[] __asm__("D_00406968");
    switch(n) {case 2:mask=1;padding=Padding2;break;case 4:mask=3;padding=Padding4;break;case 8:mask=7;padding=Padding8;break;case 16:mask=15;padding=Padding16;break;case 32:mask=31;padding=Padding32;break;default:mask=0;padding=0;}
    unsigned int old=used,end=old+count;if(end>bytes)return 0;
    used=end;void *result=(char*)buffer+old;used=end+padding[end&mask];return result;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_allocator_cleanup", func_002E5E58);
#endif
#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CFreeList::CFreeList(int bytes,unsigned int count,CAllocator *parent):CBaseAllocator(count),blockBytes(AlignedSize(bytes)),pool((AlignedSize(bytes)+AlignedSize(sizeof(CFreeListBlock)))*count,parent,count),freeBlocks(count),busyBlocks(count) {
    for(unsigned int i=0;i<count;++i){CFreeListBlock *p=new CFreeListBlock(this);freeBlocks.Append(p);}
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_allocator_cleanup", func_002E5FB8);
#endif
#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CFreeList::~CFreeList() {
    for(CVarList<CFreeListBlock*>::CIterator p(freeBlocks.head);p.node;++p)delete p.node->value;
    for(CVarList<CFreeListBlock*>::CIterator p(busyBlocks.head);p.node;++p)delete p.node->value;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_allocator_cleanup", func_002E6740);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_allocator_cleanup", func_002E69E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_allocator_cleanup", func_002E6B60);
namespace Kaim {
CBaseAllocator* CPoolBasedAllocator::Resolve(unsigned int address) {
    if (address < (unsigned int)buffer || address >= (unsigned int)buffer + bytes) return 0;
    CBaseAllocator* found = Find((void*)address);
    return found ? found : this;
}

CBaseAllocator* CFreeList::Resolve(unsigned int address) {
    return pool.Resolve(address);
}

CBaseAllocator* CFreeListBlock::Resolve(unsigned int address) {
    CBaseAllocator* found = CPoolBasedAllocator::Resolve(address);
    if (found == this) {
        --allocations;
        if (!allocations) {
            // The last allocation returns this block to the parent's available list.
            used = 0;
            parent->MakeAvailable(position);
        }
    }
    return found;
}
}
