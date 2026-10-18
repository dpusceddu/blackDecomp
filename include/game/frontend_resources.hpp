#ifndef GAME_FRONTEND_RESOURCES_HPP
#define GAME_FRONTEND_RESOURCES_HPP

// PS2 layout views; names describe behavior because original class names are unknown.
struct FrontendResourceSlot {
    char opaque[0x20];
    void* data;
};

struct FrontendResourceTable {
    int header;
    FrontendResourceSlot slots[26];
    void Release(int index) __asm__("func_00107B98");
    int Find(void* resource) __asm__("func_00107BC0");
};

struct FrontendCacheEntry {
    int key;
    void* resource;
    short variant;
    unsigned short references;
};

struct FrontendResourceCache {
    char reserved[0xd3c];
    FrontendCacheEntry entries[17];
    void* Acquire(int key, short variant) __asm__("func_00108458");
    void Release(int key, short variant) __asm__("func_001084A8");
    unsigned short ScaledCount(void* resource, float numerator, float denominator) __asm__("func_001089B0");
};

struct FrontendCallbackQueue {
    char reserved[0xe10];
    void (*callback)();
    void* callbackData;
    int Enqueue(void (*next)(), void* data) __asm__("func_001080A0");
};

typedef char FrontendResourceSlotSize[(sizeof(FrontendResourceSlot)==0x24)?1:-1];
typedef char FrontendCacheEntrySize[(sizeof(FrontendCacheEntry)==0xc)?1:-1];
#endif
