// Declarations of the Kynapse source module "sound_pool" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SOUND_POOL_HPP
#define BLACK_KYNAPSE_MODULE_SOUND_POOL_HPP
#include "kynapse/compat.hpp"

// The pool of world sound events heard by AI actors: a bounded array of events chained by
// index, per-kind live counters and reserved capacities read from the authored configuration.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);
extern void (*memoryRelease)(void*);

namespace Kaim {

void* ArrayAllocate(unsigned int size);

struct ObjectRoot {
    virtual ~ObjectRoot() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct ChildBuffers {
    const char* GetSecond() const;
    const char* GetValue() const;
};

struct AuthoredProperty {
    unsigned char unknown00[4];
    float value;
};

struct Listener {
    unsigned char unknown00[0x30];
    float x, y, z;
    AuthoredProperty* GetAuthoredProperty(const void* key);
};

extern float gNow;
extern const float kZero;
extern int gSoundKey2B4F00;
struct SoundPool;
extern SoundPool* gActiveSoundPool;

// One sound (0x24 bytes, vtable 0x2857f0, constructor 0x68990, vector deleting destructor 0x68f50).
struct SoundEvent : ObjectRoot {
    float x, y, z;
    int mask;
    int category;
    int radius;
    float expiry;
    int next;

    SoundEvent();
    virtual ~SoundEvent();
    static void* operator new[](unsigned int size) { return ArrayAllocate(size); }
    void Reset();
};

struct ClassInfoRecord;
extern ClassInfoRecord gClassInfo2BE268;

struct SoundPool : ObjectRoot {
    SoundEvent* events;
    int maxWorldSounds;
    int reservedCombat;
    int reservedWorld;
    int reservedPlayer;
    int reservedDanger;
    int reservedCarcass;
    int reservedMeat;
    int reservedGarbage;
    int counterKind1;
    int counterKind2;
    int counterKind4;
    int counterKind32;
    int counterKind8;
    int counterKind16;
    int counterKind64;
    int freeHead;
    int activeHead;
    float lastTime;

    SoundPool() : events(0), maxWorldSounds(0), freeHead(-1), activeHead(-1), lastTime(0) {}
    virtual ~SoundPool();                                     // deleting destructor 0x68e30
    virtual bool Init(ChildBuffers* config);
    virtual bool Configure(ChildBuffers* property);
    virtual bool Restart();
    virtual void Update();
    virtual ClassInfoRecord* GetClassInfo();
    virtual bool ReservationsFit();

    bool Reset();
    bool ConfigureAll(ChildBuffers* config);
    bool ConfigureBase(ChildBuffers* property);
    int* GetCounter(unsigned int mask);
    bool Matches(Listener* listener, SoundEvent* event);
    bool Hears(Listener* listener, int mask);
};





// Unmatched: the original places its failure return before the success block (19 bytes differ).




















SoundPool* CreateSoundPool();


}  // namespace Kaim

#endif
