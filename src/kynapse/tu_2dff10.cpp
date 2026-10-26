#include "include_asm.h"
#include "ps2/prelude.h"

extern "C" s32 func_0038BBB0(s32, s32, s32, s32, s32, s32);
extern M2C_UNK D_003E75A0;
extern s32 D_003E7548;

extern void (*memoryRelease)(void*);
extern "C" int _stricmp(const char*, const char*) __asm__("func_00360838");

namespace Kaim {
// Partial PS2 interfaces: unobserved members remain UNVERIFIED.
extern const char BehaviorClassKey[] __asm__("D_00405FE8");
const char BehaviorClassKey[] __attribute__((section(".rodata.behavior_class_key"), aligned(4))) = "Class";

struct Object {
    virtual ~Object() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Factory {
    unsigned int unk_0; // UNVERIFIED: the factory's first word is not accessed here.
    Object* (*create)();
};

struct FactoryProvider {
    // UNVERIFIED: these two virtual operations are not called by this TU.
    virtual ~FactoryProvider();
    virtual void Slot1();
    virtual Factory* GetFactory();
};

struct Context {
    unsigned char unk_0[0x18]; // UNVERIFIED: context fields preceding the factory provider.
    FactoryProvider* provider;
};

struct ChildBuffers {
    unsigned char unk_0[0x20]; // UNVERIFIED: only child count and accessor behavior are used here.
    unsigned int count;
    ChildBuffers* GetChild(unsigned int index) const __asm__("func_002E33E0");
    const char* GetSecond() const __asm__("func_002E3920");
};

struct Behavior : Object {
    Object* bank;
    Context* context;
    Behavior(Context*) __asm__("func_002DFF10");
    virtual ~Behavior();
    virtual bool ConfigureAll(ChildBuffers*) __asm__("func_002E0018");
    virtual bool Configure(ChildBuffers*);
};

Behavior::Behavior(Context* source) {
    bank = source->provider->GetFactory()->create();
    context = source;
}

Behavior::~Behavior() {
    delete bank;
}

bool Behavior::ConfigureAll(ChildBuffers* config) {
    for (unsigned int index = 0; index < config->count; ++index) {
        if (_stricmp(config->GetChild(index)->GetSecond(), BehaviorClassKey)) {
            if (!Configure(config->GetChild(index))) return false;
        }
    }
    return true;
}
}

extern "C" s32 func_002E00F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_0038BBB0(arg0, arg1, arg2, arg3, arg4 & 0xFF, arg5 & 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E75A0;
    return arg0;
}

extern "C" void func_002E0130(void) {
    D_003E7548 = 0;
}
