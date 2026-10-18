#ifndef GAME_FRONTEND_RESOURCES_HPP
#define GAME_FRONTEND_RESOURCES_HPP

// PS2 layout views; names describe behavior because original class names are unknown.
struct FrontendResourceSlot {
    char opaque[0x14];
    int status;
    char reserved18[8];
    void* data;
};

struct FrontendResourcePair { void* data; int flags; };

struct FrontendResourceTable {
    int header;
    FrontendResourceSlot slots[26];
    FrontendResourceSlot* selected;
    int reserved3b0;
    int selectedIndex;
    unsigned char retain;
    void Select(int index) __asm__("func_00107AB8");
    void ClearSelection() __asm__("func_00107B08");
    void SetSelectedFlags(int unused, int flags) __asm__("func_00107B78");
    void ReleaseData(void* data) __asm__("func_00107C20");
    void* GetSlotData(int index) __asm__("func_00107C80");
    void InstallPair(FrontendResourcePair* pair) __asm__("func_00107C98");
    void SetCurrentFlags(int flags) __asm__("func_00107CC8");
    int CurrentStatus() __asm__("func_00107CE8");
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
    char reserved[0xe08];
    int ioClient;
    int ioThread;
    void (*callback)(void*);
    void* callbackData;
    void Signal() __asm__("func_00107FB8");
    int Poll() __asm__("func_00108008");
    int Enqueue(void (*next)(void*), void* data) __asm__("func_001080A0");
};

typedef char FrontendResourceSlotSize[(sizeof(FrontendResourceSlot)==0x24)?1:-1];
typedef char FrontendCacheEntrySize[(sizeof(FrontendCacheEntry)==0xc)?1:-1];
#endif
