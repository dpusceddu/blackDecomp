#include "include_asm.h"

#include "kynapse/graph/allocators.hpp"
namespace Kaim {

CBaseAllocator::CBaseAllocator(unsigned int n) { owner=0;if(!n)children=0;else children=new CVarList<CBaseAllocator*>(n); }


CBaseAllocator *CBaseAllocator::Find(void *key) {
    if(!children)return 0;
    for(CVarList<CBaseAllocator*>::CIterator p(children->head);p.node;++p) {CBaseAllocator *found=p.node->value->Resolve((unsigned int)key);if(found)return found;}
    return 0;
}
bool CBaseAllocator::Remove(CBaseAllocator *value) {
    for(CVarList<CBaseAllocator*>::CIterator p(children->head);p.node;++p)if(p.node->value==value){children->Remove(p);return true;}return false;
}
void CBasicAllocator::Reset(unsigned int n,void *start,unsigned int count) {
    delete children;buffer=start;bytes=count;
    if(!n)children=0;else children=new CVarList<CBaseAllocator*>(n);
}

CAllocator *CAllocator::AllocateBlock(unsigned int count,void **out) {*out=GetBlock(count);if(*out)return this;if(next)return next->AllocateBlock(count,out);return 0;}
void *CAllocator::FindAny(unsigned int count,CBaseAllocator *requester) {
    requester->owner=0;CAllocator *p=this;
    if(p)do{void *found=p->GetBlock(count);if(found){if(requester->owner && requester->owner!=p)return 0;requester->owner=p;p->Add(requester);return found;}p=p->next;}while(p);return 0;
}
CAllocator *CFreeListBlock::AllocateBlock(unsigned int count,void **out) {*out=CPoolBasedAllocator::GetBlock(count);if(*out){++allocations;return this;}if(next)return next->AllocateBlock(count,out);return 0;}

}

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
bool CBaseAllocator::Add(CBaseAllocator *value) {
    if(children->capacity==children->activeCount)return false;
    CBaseAllocator *item=value;children->Insert(item,CVarList<CBaseAllocator*>::CIterator(0));return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E5660);
#endif
