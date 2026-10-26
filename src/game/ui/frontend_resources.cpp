#include "include_asm.h"
#include "game/aligned_buffer.h"

#include "game/frontend_resources.hpp"

extern "C" unsigned int func_00274F60(void*);
extern "C" void func_00274F58(void*,int);
extern "C" unsigned int func_00274F70(void*);
extern "C" int func_00274FD8(void*,void*);
extern "C" int func_00275340(void*);
extern "C" float func_0029D950(float);

unsigned int FrontendResourceTable::Capacity(int index) {
    return func_00274F60(&slots[index]);
}

int FrontendResourceTable::Find(void* resource) {
    FrontendResourceSlot* slot=slots;
    for (int index=0; index<26; ++index,++slot) {
        if (func_00274FD8(slot,resource)) return index;
    }
    return -1;
}

void* FrontendResourceCache::Acquire(int key, short variant) {
    FrontendResourceCache* cursor=this;
    int count=0;
    do {
        ++count;
        if (cursor->entries[0].key==key && cursor->entries[0].variant==variant) {
            ++cursor->entries[0].references;
            return cursor->entries[0].resource;
        }
        cursor=(FrontendResourceCache*)((char*)cursor+sizeof(FrontendCacheEntry));
    } while (count<17);
    return 0;
}

void FrontendResourceCache::Release(int key, short variant) {
    FrontendResourceCache* cursor=this;
    int count=0;
    do {
        ++count;
        if (cursor->entries[0].key==key && cursor->entries[0].variant==variant) {
            --cursor->entries[0].references;
            return;
        }
        cursor=(FrontendResourceCache*)((char*)cursor+sizeof(FrontendCacheEntry));
    } while (count<17);
}

unsigned short FrontendResourceCache::ScaledCount(void* resource, float numerator, float denominator) {
    int count=func_00275340(resource);
    int scaled=(int)func_0029D950(count*(numerator/denominator));
    if (count<scaled) scaled=count;
    return scaled;
}

unsigned int FrontendResourceTable::SelectBuffer(int index) {
    selectedIndex=index;
    FrontendResourceSlot* slot=&slots[index];
    selected=slot;
    func_00274F58(slot,0x80);
    return func_00274F70(selected);
}

void FrontendResourceTable::ClearSelection() {
    selected=0;
    selectedIndex=-1;
}

void FrontendResourceTable::SetSelectedAlignment(int unused, unsigned int alignment) {
    AlignedBuffer_SetAlignment((Recovered_AlignedBuffer*)selected, alignment);
}

extern "C" int func_001080F0();
extern "C" void* func_0035E7D8(unsigned int bytes);
extern FrontendResourceTable D_0040F0F0;
extern "C" void* func_00107D20(unsigned int bytes);

void* FrontendResourceTable::Allocate(unsigned int bytes) {
    if (retain || func_001080F0()) {
        return AlignedBuffer_Allocate((Recovered_AlignedBuffer*)selected, bytes);
    }
    return func_0035E7D8(bytes);
}

void* FrontendResourceTable::GetSlotData(int index) {
    return slots[index].data;
}

void* FrontendResourceTable::AllocateAligned(FrontendAllocationSpec* specification) {
    SetAlignment(specification->alignment);
    return func_00107D20(specification->bytes);
}

void FrontendResourceTable::SetAlignment(unsigned int alignment) {
    AlignedBuffer_SetAlignment((Recovered_AlignedBuffer*)selected, alignment);
}

unsigned int FrontendResourceTable::Alignment() { return selected->alignment; }

extern "C" void* func_00107CF8(unsigned int bytes) { return D_0040F0F0.Allocate(bytes); }
extern "C" void* func_00107D20(unsigned int bytes) { return D_0040F0F0.Allocate(bytes); }
extern "C" void func_00107D48() {}
extern "C" void func_00107D50() {}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/frontend_resources", func_00107B18);

#ifdef NON_MATCHING
// Unmatched: func_00108328: nested lookup control flow and register allocation.
#include "game/frontend_resources.hpp"
struct FrontendNamedResource { char reserved[0xa8]; char name[1]; };
struct FrontendNamedArchiveEntry { int reserved0,reserved4; FrontendNamedResource* resource; int reservedc; };
struct FrontendNamedArchive { int reserved0,reserved4,count; FrontendNamedArchiveEntry* entries; };
struct FrontendNamedArchiveManager {
    char reserved[0xc8c];
    FrontendNamedArchive* archives[11];
    FrontendNamedResource* Find(const char* name) __asm__("func_00108328");
};
extern FrontendResourceTable D_0040F0F0;
extern "C" int func_001080F0();
extern "C" int func_00360838(const char*,const char*);
FrontendNamedResource* FrontendNamedArchiveManager::Find(const char* name) {
    int worker=func_001080F0();
    int current=D_0040F0F0.selectedIndex;
    int all=(unsigned)(current-13)<2;
    FrontendNamedArchive** archive=archives;
    for(int index=0;index<11;++index,++archive) {
        if(*archive) {
            int bank=D_0040F0F0.Find(*archive);
            if(all || bank==1 || (worker && current==bank)) {
                FrontendNamedArchive* currentArchive=*archive;
                FrontendNamedResource* found=0;
                for(int resource=0;resource<currentArchive->count;++resource) {
                    FrontendNamedResource* object=currentArchive->entries[resource].resource;
                    if(!func_00360838(object->name,name)) { found=object; break; }
                }
                if(found) return found;
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/frontend_resources", func_00108328);
#endif

