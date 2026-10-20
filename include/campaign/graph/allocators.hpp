#ifndef BLACK_CAMPAIGN_GRAPH_ALLOCATORS_HPP
#define BLACK_CAMPAIGN_GRAPH_ALLOCATORS_HPP
#include "kynapse/compat.hpp"
#include "kynapse/point_mapper.hpp"
#include "classes/kynapse/Kaim_CFreeList.hpp"
#include "classes/kynapse/Kaim_CPoolBasedAllocator.hpp"
namespace Kaim {
struct CObject {
    virtual ~CObject() {}
    static void *operator new(unsigned int n) { return Allocate(n); }
    static void operator delete(void *p) { D_003C87E0(p); }
};
template<class T> struct CVarList : CObject {
    struct CCell : CObject {
        T value;
        CCell *previous, *next;
        unsigned char active;
        CCell():previous(0),next(0),active(0) {}
        static void *operator new[](unsigned int n) { return Allocate(n); }
        static void operator delete[](void *p) { D_003C87E0(p); }
    };
    struct CIterator : CObject {
        CCell *node;
        CIterator(CCell *p=0):node(p) {}
        CIterator &operator++(){node=node->next;return *this;}
    };
    CCell *storage,*head,*tail,*freeHead;
    unsigned int activeCount,capacity;
    CVarList(unsigned int n) {
        head=0;activeCount=0;capacity=n;freeHead=0;storage=0;tail=0;
        if(n) {
            storage=new CCell[n];
            freeHead=storage;
            storage[0].previous=0;
            for(unsigned int i=1;i<capacity;++i) {
                storage[i].previous=&storage[i-1];
                storage[i].previous->next=&storage[i];
            }
            storage[capacity-1].next=0;
        }
    }
    virtual ~CVarList() { if(capacity && storage) delete[] storage; }
    void Append(const T &value) {
        CCell *entry=freeHead;
        if(entry) {
            ++activeCount;freeHead=entry->next;entry->value=value;entry->active=1;
            if(!tail) {
                tail=entry;head=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;
            } else {entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;}
        }
    }
    CIterator Insert(const T &value,CIterator before) {
        CCell *entry=freeHead;
        if(!entry)return CIterator(0);
        ++activeCount;freeHead=entry->next;entry->value=value;entry->active=1;
        if(!before.node) {
            if(!tail){head=entry;tail=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;return CIterator(entry);}
            entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;return CIterator(entry);
        }
        CCell *previous=before.node->previous;entry->next=before.node;before.node->previous=entry;entry->previous=previous;
        if(previous)previous->next=entry;else head=entry;
        return CIterator(entry);
    }
    void Remove(const CIterator &at) {
        CCell *node=at.node;node->active=0;
        if(node==head)head=node->next;
        if(node==tail)tail=node->previous;
        if(node->previous)node->previous->next=node->next;
        if(node->next)node->next->previous=node->previous;
        node->next=freeHead;freeHead=node;--activeCount;
    }
};
struct CBaseAllocator : CObject {
    CBaseAllocator(unsigned int);
    virtual ~CBaseAllocator();
    virtual CBaseAllocator *Resolve(unsigned int);
    virtual CBaseAllocator *Find(void *);
    virtual bool Add(CBaseAllocator *);
    virtual bool Remove(CBaseAllocator *);
    CBaseAllocator *owner;
    CVarList<CBaseAllocator*> *children;
};
struct CAllocator : CBaseAllocator {
    CAllocator(unsigned int n):CBaseAllocator(n) {}
    virtual ~CAllocator();
    virtual CAllocator *AllocateBlock(unsigned int,void **);
    virtual void *FindAny(unsigned int,CBaseAllocator *);
    virtual void *GetBlock(unsigned int);
    virtual void Release(unsigned int);
    CAllocator *next;
};
struct CPoolBasedAllocator : CAllocator {
    CPoolBasedAllocator(int,CAllocator*,unsigned int);
    CPoolBasedAllocator(void*,int,CAllocator*,unsigned int);
    virtual ~CPoolBasedAllocator();
    virtual CBaseAllocator *Resolve(unsigned int);
    virtual void *GetBlock(unsigned int);
    void *buffer;
    unsigned int bytes,used,unused;
};
struct CFreeListBlock;
struct CFreeList : CBaseAllocator {
    CFreeList(int,unsigned int,CAllocator*);
    virtual ~CFreeList();
    virtual CBaseAllocator *Resolve(unsigned int);
    int blockBytes;
    CPoolBasedAllocator pool;
    CVarList<CFreeListBlock*> freeBlocks,busyBlocks;
    void MakeAvailable(CVarList<CFreeListBlock*>::CIterator);
    CFreeListBlock *TakeBlock();
};
struct CFreeListBlock : CPoolBasedAllocator {
    CFreeListBlock(CFreeList*) __asm__("func_002E70F0");
    virtual ~CFreeListBlock();
    virtual CBaseAllocator *Resolve(unsigned int);
    virtual CAllocator *AllocateBlock(unsigned int,void **);
    CFreeList *parent;
    unsigned int allocations;
    CVarList<CFreeListBlock*>::CIterator position;
};
struct CBasicAllocator : CAllocator { void *buffer;unsigned int bytes;CBasicAllocator(unsigned int n):CAllocator(n) {} void Reset(unsigned int,void*,unsigned int); };
extern int (*AllocatorAlignment)() __asm__("D_00451244");
inline int ValidAlignment() {
    int n=8;
    if(AllocatorAlignment) {
        n=AllocatorAlignment();
        if(n!=2 && n!=4 && n!=8 && n!=16 && n!=32)n=8;
    }
    return n;
}
inline unsigned int AlignedSize(unsigned int n) { unsigned int alignment=ValidAlignment();unsigned int r=n%alignment;if(r==0)return n;return n+alignment-r; }
typedef char AllocatorCellSize[sizeof(CVarList<CBaseAllocator*>::CCell)==20?1:-1];
typedef char AllocatorListSize[sizeof(CVarList<CBaseAllocator*>)==28?1:-1];
typedef char PoolAllocatorSize[sizeof(CPoolBasedAllocator)==32?1:-1];
typedef char FreeListBlockSize[sizeof(CFreeListBlock)==48?1:-1];
// Complete unused interfaces and the semantic ownership of unaccessed fields remain UNVERIFIED.
}
#endif
