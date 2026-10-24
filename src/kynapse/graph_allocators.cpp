#include "kynapse/graph/allocators.hpp"
namespace Kaim {
CBaseAllocator::CBaseAllocator(unsigned int n) { owner=0;if(!n)children=0;else children=new CVarList<CBaseAllocator*>(n); }


CBaseAllocator *CBaseAllocator::Find(void *key) {
    if(!children)return 0;
    for(CVarList<CBaseAllocator*>::CIterator p(children->head);p.node;++p) {CBaseAllocator *found=p.node->value->Resolve((unsigned int)key);if(found)return found;}
    return 0;
}
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
bool CBaseAllocator::Add(CBaseAllocator *value) {
    if(children->capacity==children->activeCount)return false;
    CBaseAllocator *item=value;children->Insert(item,CVarList<CBaseAllocator*>::CIterator(0));return true;
}
#endif
bool CBaseAllocator::Remove(CBaseAllocator *value) {
    for(CVarList<CBaseAllocator*>::CIterator p(children->head);p.node;++p)if(p.node->value==value){children->Remove(p);return true;}return false;
}
void CBasicAllocator::Reset(unsigned int n,void *start,unsigned int count) {
    delete children;buffer=start;bytes=count;
    if(!n)children=0;else children=new CVarList<CBaseAllocator*>(n);
}
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CPoolBasedAllocator::CPoolBasedAllocator(int n,CAllocator *parent,unsigned int childrenCount):CAllocator(childrenCount) {
    next=parent;bytes=AlignedSize(n);buffer=parent->FindAny(bytes,this);
    if(!buffer)bytes=0;used=0;unused=0;
}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CPoolBasedAllocator::CPoolBasedAllocator(void *p,int n,CAllocator *parent,unsigned int childrenCount):CAllocator(childrenCount) {
    next=parent;buffer=p;bytes=AlignedSize(n);used=0;unused=0;if(parent)parent->Add(this);
}
#endif

#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
void *CPoolBasedAllocator::GetBlock(unsigned int count) {
    if(!count)count=1;
    int n=ValidAlignment();unsigned int mask;const int *padding;
    extern const int Padding2[] __asm__("D_004068F0");extern const int Padding4[] __asm__("D_004068F8");extern const int Padding8[] __asm__("D_00406908");extern const int Padding16[] __asm__("D_00406928");extern const int Padding32[] __asm__("D_00406968");
    switch(n) {case 2:mask=1;padding=Padding2;break;case 4:mask=3;padding=Padding4;break;case 8:mask=7;padding=Padding8;break;case 16:mask=15;padding=Padding16;break;case 32:mask=31;padding=Padding32;break;default:mask=0;padding=0;}
    unsigned int old=used,end=old+count;if(end>bytes)return 0;
    used=end;void *result=(char*)buffer+old;used=end+padding[end&mask];return result;
}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CFreeList::CFreeList(int bytes,unsigned int count,CAllocator *parent):CBaseAllocator(count),blockBytes(AlignedSize(bytes)),pool((AlignedSize(bytes)+AlignedSize(sizeof(CFreeListBlock)))*count,parent,count),freeBlocks(count),busyBlocks(count) {
    for(unsigned int i=0;i<count;++i){CFreeListBlock *p=new CFreeListBlock(this);freeBlocks.Append(p);}
}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CFreeList::~CFreeList() {
    for(CVarList<CFreeListBlock*>::CIterator p(freeBlocks.head);p.node;++p)delete p.node->value;
    for(CVarList<CFreeListBlock*>::CIterator p(busyBlocks.head);p.node;++p)delete p.node->value;
}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
void CFreeList::MakeAvailable(CVarList<CFreeListBlock*>::CIterator at) {freeBlocks.Append(at.node->value);busyBlocks.Remove(at);}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CFreeListBlock *CFreeList::TakeBlock() {
    CVarList<CFreeListBlock*>::CIterator at(freeBlocks.head);if(!at.node)return 0;
    CFreeListBlock *p=at.node->value;freeBlocks.Remove(at);busyBlocks.Append(p);return p;
}
#endif
CAllocator *CAllocator::AllocateBlock(unsigned int count,void **out) {*out=GetBlock(count);if(*out)return this;if(next)return next->AllocateBlock(count,out);return 0;}
void *CAllocator::FindAny(unsigned int count,CBaseAllocator *requester) {
    requester->owner=0;CAllocator *p=this;
    if(p)do{void *found=p->GetBlock(count);if(found){if(requester->owner && requester->owner!=p)return 0;requester->owner=p;p->Add(requester);return found;}p=p->next;}while(p);return 0;
}
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CBaseAllocator *CPoolBasedAllocator::Resolve(unsigned int address) {if(address>=(unsigned int)buffer){if(address<(unsigned int)buffer+bytes){CBaseAllocator *p=Find((void*)address);if(p)return p;return this;}}return 0;}
#endif
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CBaseAllocator *CFreeList::Resolve(unsigned int address) {if(address>=(unsigned int)pool.buffer){if(address<(unsigned int)pool.buffer+pool.bytes){CBaseAllocator *p=pool.Find((void*)address);if(p)return p;return &pool;}}return 0;}
#endif
CAllocator *CFreeListBlock::AllocateBlock(unsigned int count,void **out) {*out=CPoolBasedAllocator::GetBlock(count);if(*out){++allocations;return this;}if(next)return next->AllocateBlock(count,out);return 0;}
#if 0
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CBaseAllocator *CFreeListBlock::Resolve(unsigned int address) {CBaseAllocator *p=CPoolBasedAllocator::Resolve(address);if(p==this){if(!--allocations){used=0;parent->MakeAvailable(position);}}return p;}
#endif

}
