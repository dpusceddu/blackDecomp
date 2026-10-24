#include "include_asm.h"

#include "kynapse/agents/sound.hpp"

namespace Kaim {
extern int gTeamKey;
struct IntProperty { int unused; int value; };

static inline float DistanceSquared(const SoundEvent* sound,const Listener* listener) {
    const Vec3& a=*(const Vec3*)&sound->x;
    const Vec3& b=*(const Vec3*)&listener->x;
    float dz=a.z-b.z;
    float dx=a.x-b.x;
    float dy=a.y-b.y;
    return dz*dz+dx*dx+dy*dy;
}


bool SoundPool::Init(ChildBuffers* config)
{
    maxWorldSounds = 0x40;
    reservedCombat = 1;
    reservedWorld = 1;
    reservedPlayer = 1;
    reservedDanger = 1;
    reservedCarcass = 1;
    reservedMeat = 1;
    reservedGarbage = 1;
    lastTime = gNow;
    if (!config)
        return false;
    if (!ConfigureAll(config))
        return false;
    if (!ReservationsFit())
        return false;
    events = new SoundEvent[maxWorldSounds];
    if (!Reset())
        return false;
    gActiveSoundPool = this;
    return true;
}

SoundPool::~SoundPool()
{
    delete[] events;
    events = 0;
    gActiveSoundPool = 0;
}

SoundPool* CreateSoundPool()
{
    return new SoundPool;
}

Listener* SoundPool::FindLoudest(Listener* listener) {
    Listener* best=0;
    float level=0;
    Update();
    for(int index=activeHead;index!=-1;index=events[index].next) {
        SoundEvent* sound=&events[index];
        Listener* owner=sound->owner;
        if(owner && owner!=listener) {
            float ratio=float(sound->radius*sound->radius)/DistanceSquared(sound,listener);
            if(level<ratio) { level=ratio;best=owner; }
        }
    }
    AuthoredProperty* property=listener->GetAuthoredProperty(&gSoundKey2B4F00);
    if(property) { if(1.0f/level<property->value*property->value)return best; return 0; }
    return best;
}

Listener* SoundPool::FindEnemySound(Listener* listener) {
    Listener* best=0;
    float level=0;
    Update();
    IntProperty* own=(IntProperty*)listener->GetAuthoredProperty(&gTeamKey);
    if(own) {
        if(own->value==-1)return 0;
        for(int index=activeHead;index!=-1;index=events[index].next) {
            SoundEvent* sound=&events[index];
            if(sound->owner) {
                IntProperty* team=(IntProperty*)sound->owner->GetAuthoredProperty(&gTeamKey);
                if(team && team->value!=own->value && team->value!=-1) {
                    float ratio=float(sound->radius*sound->radius)/DistanceSquared(sound,listener);
                    if(level<ratio){best=sound->owner;level=ratio;}
                }
            }
        }
        AuthoredProperty* property=listener->GetAuthoredProperty(&gSoundKey2B4F00);
        if(!property)return best;
        if(1.0f/level<property->value*property->value)return best;
    }
    return 0;
}

bool SoundPool::Reset()
{
    freeHead = 0;
    activeHead = -1;
    int i;
    for(i=0;i<maxWorldSounds;++i) {
            events[i].Reset();
            events[i].next = i + 1;
    }
    events[i - 1].next = -1;
    counterKind1 = 0;
    counterKind2 = 0;
    counterKind4 = 0;
    counterKind32 = 0;
    counterKind8 = 0;
    counterKind16 = 0;
    counterKind64 = 0;
    return true;
}

int SoundPool::Count(int mode) {
    Update();
    int count=counterKind1+counterKind2+counterKind4+counterKind32+counterKind8+counterKind16+counterKind64;
    if(mode==1)return maxWorldSounds-count;
    if(mode==2)return count;
    return 0;
}

SoundEvent* SoundPool::GetSound(int index) {
    if(index>maxWorldSounds-1)return 0;
    if(index<0)return 0;
    return &events[index];
}

// Unmatched: Configure and Collect retain different failure-branch layouts.
// Unmatched: ReserveSound and FindLoudestAt retain register-allocation differences.
// Unmatched: Hears, EmitSound, AddSound, Update and Draw retain inline/scheduling differences.
// Unmatched: Matches retains vector accessor scheduling differences.
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D1F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D5F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DAA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DC28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DDE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E558);
