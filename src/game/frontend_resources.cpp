#include "game/frontend_resources.hpp"

extern "C" void func_00274F60(void*);
extern "C" int func_00274FD8(void*,void*);
extern "C" int func_00275340(void*);
extern "C" float func_0029D950(float);

void FrontendResourceTable::Release(int index) {
    func_00274F60(&slots[index]);
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
