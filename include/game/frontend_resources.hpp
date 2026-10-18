#ifndef GAME_FRONTEND_RESOURCES_HPP
#define GAME_FRONTEND_RESOURCES_HPP

// PS2 layout views; names describe behavior because original class names are unknown.
extern "C" void* func_001282D0(void*);
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

struct FrontendVirtualEntry {
    short adjustment;
    short reserved;
    int (*function)(void*);
};
struct FrontendUpdateTarget {
    int reserved;
    FrontendVirtualEntry* virtualTable;
};
struct FrontendLoadingState {
    int state;
    FrontendUpdateTarget* owner;
    FrontendVirtualEntry* virtualTable;
    int reservedc;
    long request, result;
    unsigned flags;
    unsigned char waiting, forced;
    short reserved26;
    float timeout, elapsed;
    void* specification;
    void Update() __asm__("func_00106200");
    int Enter() __asm__("func_00106080");
};
struct FrontendSequentialLoadingState {
    int state;
    FrontendUpdateTarget* owner;
    FrontendVirtualEntry* virtualTable;
    char counter[0x1c];
    long request, result;
    unsigned flags;
    unsigned char waiting, forced;
    short reserved3e;
    float timeout, elapsed;
    void* specification;
    void Update() __asm__("func_001069F8");
    int Enter() __asm__("func_00106868");
};

struct FrontendControllerSample { char opaque[0xf0]; };
struct FrontendControllerChannel { char opaque[0x16c]; };
struct FrontendControllerScreen {
    char reserved[0x2c0];
    FrontendControllerSample samples[2];
    FrontendControllerChannel channels[2];
    int state;
    unsigned char feedback[0x20];
    unsigned char feedbackEnabled;
    char reserved79d[11];
    char textBox[1];
    int Enter() __asm__("func_00107020");
    void Update() __asm__("func_00107228");
};

struct FrontendMenuState {
    int state;
    char reserved4[0x40];
    int pending;
    int mode;
    char loader[0x1bc];
    int currentScreen, requestedScreen, forced;
    int reserved214;
    char message[0xb30];
    float elapsed;
    unsigned char initialized, musicStarted;
    short reservedd4e;
    void* archive;
    void Initialize() __asm__("func_001041A8");
    int Enter() __asm__("func_00104210");
    void Update() __asm__("func_001046B0");
    int Exit() __asm__("func_00104E10");
    void Destroy() __asm__("func_00105058");
    void Request(int screen, int force) __asm__("func_001040F8");
    int Load(const char* name, int kind, int force) __asm__("func_001040D8");
    void ChangeMode(int next) __asm__("func_00105228");
    void MarkPending() __asm__("func_00105258");
};
struct FrontendScreenManager {
    char reserved[0x3820];
    char requestedName[0x20];
    signed char alternate;
    char reserved3841[0x43];
    int alternatePending;
    int reserved3888;
    int primaryPending;
};

typedef char FrontendVirtualEntrySize[(sizeof(FrontendVirtualEntry)==8)?1:-1];
typedef char FrontendLoadingStateSize[(sizeof(FrontendLoadingState)==0x38)?1:-1];
typedef char FrontendSequentialLoadingStateSize[(sizeof(FrontendSequentialLoadingState)==0x50)?1:-1];
typedef char FrontendResourceSlotSize[(sizeof(FrontendResourceSlot)==0x24)?1:-1];
typedef char FrontendCacheEntrySize[(sizeof(FrontendCacheEntry)==0xc)?1:-1];
typedef char FrontendMenuStateSize[(sizeof(FrontendMenuState)==0xd54)?1:-1];
#endif
