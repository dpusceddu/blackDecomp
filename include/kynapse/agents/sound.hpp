// PS2 sound manager/event layouts, checked by the exact initialization, destruction and query methods.
#ifndef BLACK_CONTEXT_BEHAVIORS_SOUND_HPP
#define BLACK_CONTEXT_BEHAVIORS_SOUND_HPP
#include "kynapse/compat.hpp"
#include "kynapse/property.hpp"
#include "ps2/vector_storage.hpp"

// The pool of world sound events heard by AI actors: a bounded array of events chained by
// index, per-kind live counters and reserved capacities read from the authored configuration.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);
extern void (*memoryRelease)(void*);

namespace Kaim {
struct Vec3 { float x,y,z;
 Vec3() {}
 Vec3(float a,float b,float c):x(a),y(b),z(c){}
 Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z){}
 Vec3& operator=(const Vec3& v) { x=v.x;y=v.y;z=v.z;return *this; }
 bool operator==(const Vec3& b) const { if(x==b.x && y==b.y && z==b.z)return true;return false; }
};

void* ArrayAllocate(unsigned int size);

struct ObjectRoot {
    virtual ~ObjectRoot() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
    static void operator delete[](void* block) { memoryRelease(block); }
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

// Sound events occupy 0x24 bytes on PS2.
struct SoundEvent : ObjectRoot {
    float x, y, z;
    union { int mask; Listener* owner; };
    int category;
    int radius;
    float expiry;
    int next;

    SoundEvent() : mask(0) {}
    virtual ~SoundEvent() { mask=0; }
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
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

    SoundPool() __asm__("func_0030D1F8");
    virtual ~SoundPool();
    virtual bool Init(ChildBuffers* config);
    virtual bool Configure(ChildBuffers* property);
    virtual bool Restart();
    virtual void Update();
    virtual ClassInfoRecord* GetClassInfo();
    virtual bool ReservationsFit();

    bool Reset();
    bool ConfigureAll(ChildBuffers* config);
    bool ConfigureBase(ChildBuffers* property) { return BlackPS2::Kynapse::IsPrivateProperty(property); }
    int* GetCounter(unsigned int mask);
    bool Matches(Listener* listener, SoundEvent* event);
    bool Hears(Listener* listener, int mask);
    void RemoveSound(int index,int previous) __asm__("func_0030E278");
    int Count(int mode) __asm__("func_0030E4B8");
    SoundEvent* GetSound(int index) __asm__("func_0030E560");
    bool AddSound(unsigned kind,const Vec3& position,int radius,Listener* owner,float duration) __asm__("func_0030E320");
    void Draw() __asm__("func_0030E8D8");
    int ReserveSound(unsigned kind) __asm__("func_0030D5F8");
    int* GetReservedCount(unsigned kind) __asm__("func_0030E728");
    Listener* FindLoudest(Listener* listener) __asm__("func_0030D770");
    Listener* FindEnemySound(Listener* listener) __asm__("func_0030D8D0");
    SoundEvent* FindLoudestAt(const Vec3& position) __asm__("func_0030DAA8");
    int Collect(Listener* listener, SoundEvent** output, int capacity, unsigned kinds) __asm__("func_0030DDE8");

};

typedef char SoundPoolSize[sizeof(SoundPool)==0x50?1:-1];
typedef char SoundEventSize[sizeof(SoundEvent)==0x24?1:-1];
SoundPool* CreateSoundPool();

}  // namespace Kaim

#endif
