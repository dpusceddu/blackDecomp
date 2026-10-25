#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/effects/runtime.hpp"
// Mod effect queues claimed before native reconstruction.
#endif

#ifdef NON_MATCHING
// Unmatched: actor attachment and matrix operator context; native allocation and branch order.
#include "game/effects/runtime.hpp"
#include "game/effects/vu_math.h"
using Effects::Matrix;
struct AttachmentActor {char unknown00[0x70];Matrix world;char unknownb0[0x1f4];char*definition;char unknown2a8[0x88];void*pose;};
struct Attachment : Effects::AttachmentManager {
 void Update() __asm__("func_001B64C0");int Clear() __asm__("func_001B6910");void Detach(void*,long) __asm__("func_001B6CF8");void Flush(float) __asm__("func_001B6DC8");void Deferred(float) __asm__("func_001B7160");
};
extern "C" {extern char*D_0040F4D0,*D_0040F4E0;void func_001B1518(void*);void func_001B15A0(void*);void func_001B11A0(void*,const Matrix*);int func_001B1340(float,float,void*,void*);Matrix*func_001A68E0(void*,int);unsigned long func_00136B30(void*);int func_0015D2E8(void*,unsigned long);char*func_0015D248(void*,unsigned long,int);}
static inline Matrix Product(const Matrix&m,const Matrix&n){Matrix r;r.row[0]=BkEffectRotatePS2(m.row,n.row[0]);r.row[1]=BkEffectRotatePS2(m.row,n.row[1]);r.row[2]=BkEffectRotatePS2(m.row,n.row[2]);r.row[3]=BkEffectTransformPS2(m.row,n.row[3]);return r;}
void Attachment::Update(){float now=*(float*)(D_0040F4D0+0x20);Flush(previousTime);Deferred(now);short remaining=activeCount-1;unsigned short *cursor=indices;while(remaining!=-1){unsigned short index=*cursor;AttachmentActor *actor=(AttachmentActor*)actors[index];if(actor){Matrix transform;int kind=kinds[index];if(kind==8){if(modes[index]==0){Effects::IdentityXYZ(transform);transform.row[3]=actor->world.row[3];}else if(modes[index]==1)transform=actor->world;func_001B11A0(entries+index,&transform);}else{transform=*func_001A68E0(actor->pose,kind);Matrix*result=&transform;Matrix adjusted;if(kind==0){Matrix correction,offset;Effects::IdentityXYZ(correction);Effects::IdentityXYZ(offset);unsigned long key=func_00136B30(actor);if(func_0015D2E8(D_0040F4E0,key)){char *context=func_0015D248(D_0040F4E0,key,0);correction.row[3]=*(s128*)(context+0x80);adjusted=Product(transform,correction);if(actor->definition[0x108]){char *resource=*(char**)(actor->definition+0xe8);resource=*(char**)(resource+0x10);float height=*(float*)(resource+0x48);BkEffectPointPS2 translation={0,0,height,0};offset.row[3]=*(s128*)&translation;adjusted=Product(adjusted,offset);}result=&adjusted;func_001B11A0(entries+index,result);}}else func_001B11A0(entries+index,result);}}if(!func_001B1340(now,previousTime,entries+index,*(void**)((char*)this+0x344c))){func_001B1518(entries+index);unsigned short last=activeCount-1;unsigned short*reverse=*(unsigned short**)((char*)this+0x3444);unsigned short old=reverse[index],moved=indices[last];indices[old]=moved;reverse[index]=last;indices[last]=index;reverse[moved]=old;activeCount--;}else cursor++;remaining--;}previousTime=now;}
int Attachment::Clear(){unsigned short i=0;do{if(entries[i].resource){func_001B1518(entries+i);actors[i]=0;kinds[i]=8;modes[i]=-1;}i++;}while(i<80);activeCount=0;pending=0;return 1;}
void Attachment::Detach(void*actor,long stop){unsigned short i=0;do{if(actors[i]==actor){if(stop&&entries[i].resource)func_001B15A0(entries+i);actors[i]=0;kinds[i]=8;}i++;}while(i<80);}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B64C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6CF8);
#endif


#ifdef NON_MATCHING
// Unmatched: named-resource lookup, mixed-width call contracts and VU temporary lifetimes.
#include "game/effects/runtime.hpp"
#include "ps2/vu0.hpp"

// Types below are local instruction views; canonical shared headers are untouched.
namespace Effects {
template<class T> inline T& At(void *p,unsigned offset) { return *(T*)((char*)p+offset); }
struct Name {
    unsigned long value;
    inline int LastDigit() const { return (int)(value % (unsigned long)40); }
    inline Name Pop() const { Name n={value/(unsigned long)40}; return n; }
};
struct Actor {
    unsigned char unknown00[0x70]; Matrix world;
    unsigned char unknownB0[0x14]; int kind;
};
struct AttachmentAsset {
    unsigned char unknown00[0x240]; unsigned short deferredIndex;
    unsigned char extraEmitter,unknown243[0x2d]; signed char pulse;
    unsigned char unknown271[3]; float pulseDelay,pulseHold;
    unsigned char unknown27c[4]; Name childAsset; float childOffset;
    unsigned char unknown28c[4]; float gain,range,rise,fall;
    unsigned char trail,unknown2a1[3]; float trailGain,trailRate;
    unsigned char unknown2ac[4]; Value trailColor;
};
struct Group {
    short count; unsigned char randomPoint,unknown03;
    AttachmentAsset *assets[8]; float delays[8];
};
template<class T> struct NameMap {
    struct Pair { Name key; T *value; unsigned unknown0c; };
    unsigned char unknown00[8]; int count; Pair *pairs;
    inline T *Find(Name name) const {
        for(int i=0;i<count;++i) if(pairs[i].key.value==name.value) return pairs[i].value;
        return 0;
    }
};
struct DeferredConfig { Name identity; unsigned char unknown08[8]; float height; unsigned char unknown14[0x34]; };
struct Resources {
    unsigned char unknown00[8]; NameMap<AttachmentAsset> *assets; NameMap<Group> *groups;
    unsigned char unknown10[0x10]; DeferredConfig *deferred;
};
struct Request {
    Matrix world; AttachmentAsset *asset; Actor *actor; int part,mode;
    float offset; unsigned char unknown54[0xc];
};
struct Deferred { Entry *entry; DeferredConfig *config; float when; };
struct Tail {
    unsigned short *indices,*freeIndices;
    unsigned short active,end; void *owner; Resources *resources;
    float previousTime; unsigned short queued,unknown1a;
};
class AttachmentRecovery : public AttachmentManager {
public:
    inline Tail& State() { return At<Tail>(this,0x3440); }
    inline Request& Queued(unsigned i) { return At<Request>(this,0x26c0+i*sizeof(Request)); }
    inline Deferred& Later(unsigned i) { return At<Deferred>(this,0x32c0+i*sizeof(Deferred)); }
    void Queue(Name,Actor*,int,int) __asm__("func_001B69E0");                  // 001B69E0
    void Consume(float) __asm__("func_001B6DC8");                             // 001B6DC8
    void Expire(float) __asm__("func_001B7160");                              // 001B7160
    Value RandomPoint(Actor*) __asm__("func_001B72E0");                        // 001B72E0: full128 V0 result
};
typedef char RequestIs60[sizeof(Request)==0x60?1:-1];
typedef char DeferredIsC[sizeof(Deferred)==0xc?1:-1];
typedef char GroupDelays24[(unsigned)&((Group*)0)->delays==0x24?1:-1];
extern "C" {
extern void *D_0040F4C4,*D_0040F4C0,*D_0040F4D0,*D_0040F510;
extern Value D_004432A0;
void *func_00108120(void*,unsigned long);
unsigned long func_001A68E0(void*);
// Five FPU args F12..16; GP args are ownerA0, resourceA1, transformA2.
void func_001BE7F0(float,float,float,float,float,void*,void*,const Matrix*);
// Three FPU args, ownerA0, FULL128 color A1.
void func_001B0C10(float,float,float,void*,Value);
void func_001BEBA0(float,float,void*,Entry*,AttachmentAsset*);
void func_001EC158(void*,signed char,Value);
void func_001EC060(float,void*,Value,int,Actor*);
void func_001B1318(Matrix*,Entry*);
void func_001BEF70(void*,Value);
void func_0014EBE0(void*,Matrix*,DeferredConfig*);
void func_00152BB0(Actor*,Matrix*,Game::Position4*);
unsigned long func_001484C8(Actor*);
int func_0014A650(Actor*,unsigned long);
float func_0014A568(Actor*,unsigned long);
void func_0014A6A0(Actor*,unsigned long,int,Matrix*,Game::Position4*);
float func_0012D0D0(float,float,void*);
}

void AttachmentRecovery::Queue(Name name,Actor *actor,int mode,int part)
{
    AttachmentAsset *asset=0;
    Group *group=0;
    int count;
    if(name.LastDigit()==38 && name.Pop().LastDigit()==38) {
        if(!State().resources->groups) return;
        group=State().resources->groups->Find(name);
        if(!group) return;
        count=group->count;
    } else {
        asset=State().resources->assets->Find(name);
        if(!asset) return;
        count=1;
    }
    float offset=0;
    Actor *follow=actor;
    for(short i=0;i<count;++i) {
        if(State().queued>31) return;
        Matrix world;
        if(mode==0) {
            world.row[3]=actor->world.row[3];
            Matrix identity; IdentityXYZ(identity);
            world.row[0]=identity.row[0];world.row[1]=identity.row[1];world.row[2]=identity.row[2];
        } else if(mode==1) world=actor->world;
        // Other mode values deliberately leave the same unspecified matrix lanes.
        if(group) {
            offset=group->delays[i]; asset=group->assets[i];
            if(group->randomPoint) {
                follow=0;
                world.row[3]=Ps2Math::VU0::TransformPoint(actor->world.row,RandomPoint(actor));
            }
        }
        Request&request=Queued(State().queued);
        request.world=world;
        Queued(State().queued).actor=follow;
        Queued(State().queued).asset=asset;
        Queued(State().queued).mode=mode;
        Queued(State().queued).part=part;
        Queued(State().queued).offset=offset;
        ++State().queued;
    }
}

void AttachmentRecovery::Consume(float now)
{
    unsigned short cursor=State().queued-1;
    if(State().queued) do {
        if(State().active==State().end) break;
        Request&request=Queued(cursor);
        AttachmentAsset *asset=request.asset;
        unsigned short slot=State().indices[State().active++];
        Entry *entry=&entries[slot];
        float born=now+request.offset;
        entry->Initialize(&request.world,(char*)asset,1,born);
        actors[slot]=request.actor;kinds[slot]=request.part;modes[slot]=request.mode;
        if(asset->childAsset.value) {
            void *resource=func_00108120(D_0040F4C4,asset->childAsset.value);
            if(request.part==8) {
                func_001BE7F0(asset->gain,request.offset+asset->childOffset,asset->range,asset->rise,asset->fall,
                              (char*)State().owner+0x83720,resource,&request.world);
            } else {
                // 1A68E0 result is carried in full64 A2. Here reinterpreted as a
                // transform handle only; semantic ownership/protocol is uncertain.
                unsigned long pose=func_001A68E0(At<void*>(request.actor,0x330));
                func_001BE7F0(asset->gain,request.offset,asset->range,asset->rise,asset->fall,
                              (char*)State().owner+0x83720,resource,(const Matrix*)pose);
            }
        }
        if(asset->trail) {
            func_001B0C10(asset->trailGain,asset->trailRate,request.offset,
                         (char*)D_0040F4C0+0xd290,asset->trailColor);
        }
        if(asset->extraEmitter) {
            func_001BEBA0(request.offset,10.0f,(char*)State().owner+0x83d24,entry,asset);
        }
        if(asset->deferredIndex!=9999) {
            unsigned short i=0;
            while(i<32 && Later(i).when!=-1.0f) ++i;
            if(i<32) {
                Later(i).when=born;
                Later(i).entry=entry;
                Later(i).config=&State().resources->deferred[asset->deferredIndex];
            }
        }
        void *presentation=At<void*>(D_0040F510,0xcbd8);
        void *pulseSystem=At<void*>(presentation,0x24);
        if(asset->pulse>0) func_001EC158(pulseSystem,asset->pulse,request.world.row[3]);
        if(asset->pulseHold>0.0f) {
            func_001EC060(request.offset+asset->pulseDelay,pulseSystem,request.world.row[3],1,(Actor*)actors[slot]);
        }
        if(cursor==0) break;
        --cursor;
    } while(State().active!=State().end);
    State().queued=0;
}

// The Y-only lane operators follow the actual VU instruction direction; the
// untouched lanes remain unspecified, as in the original inline vector layer.
static inline Value RaiseY(Value point,float amount)
{
    Value scalar=Game::BitsVec(*(int*)&amount),sum,result=point;
    asm("vaddx.y sumv, pointv, scalarvx\n\tvaddy.y resultv, vf0, sumvy\n\tvmove.xyzw resultv, resultv"
        : "=&j sumv"(sum),"+j resultv"(result)
        : "j pointv"(point),"j scalarv"(scalar));
    return result;
}
void AttachmentRecovery::Expire(float now)
{
    for(unsigned short i=0;i<32;++i) {
        Deferred&scheduled=Later(i);
        if(scheduled.when!=-1.0f && scheduled.when<now) {
            Matrix transform;
            func_001B1318(&transform,scheduled.entry);
            Matrix raised=transform;
            raised.row[3]=RaiseY(transform.row[3],scheduled.config->height);
            if(scheduled.config->identity.value==(unsigned long)0x9b5db9da662d3b18) {
                func_001BEF70((char*)State().owner+0x83fb0,raised.row[3]);
                scheduled.entry=0;
            } else {
                // Original empty construction loop for four inline vector rows.
                Matrix temporary;
                for(int row=3;row!=-1;--row) {}
                unsigned char output[0x60];
                func_0014EBE0(output,&raised,scheduled.config);
                scheduled.entry=0;
            }
            scheduled.when=-1.0f;
            scheduled.config=0;
        }
    }
}

static inline float BoxVolume(const Game::Position4&extent)
{
    Value input=Game::Load(extent),eight=Game::BitsVec(0x41000000),result;
    asm("vmuly.x resultv, extentv, extentvy\n\tvmulz.x resultv, resultv, extentvz\n\tvmulx.x resultv, resultv, eightvx"
        : "=j resultv"(result) : "j extentv"(input),"j eightv"(eight));
    return Game::X(result);
}
static inline float NegativeComponent(const Game::Position4&extent,int lane)
{
    Value in=Game::Load(extent),negative;
    if(lane==0) {asm("vsub.x outputv, vf0, inputv":"=j outputv"(negative):"j inputv"(in));return Game::X(negative);}
    Game::Position4 spilled;
    if(lane==1) {asm("vsub.y outputv, vf0, inputv":"=j outputv"(negative):"j inputv"(in));Game::Store(spilled,negative);return spilled.y;}
    asm("vsub.z outputv, vf0, inputv":"=j outputv"(negative):"j inputv"(in));Game::Store(spilled,negative);return spilled.z;
}
static inline void SetComponent(Value&point,float number,int lane)
{
    Value scalar=Game::BitsVec(*(int*)&number),result=point;
    if(lane==0) asm("vaddx.x outputv, vf0, scalarvx":"+j outputv"(result):"j scalarv"(scalar));
    else if(lane==1) asm("vaddx.y outputv, vf0, scalarvx":"+j outputv"(result):"j scalarv"(scalar));
    else asm("vaddx.z outputv, vf0, scalarvx":"+j outputv"(result):"j scalarv"(scalar));
    // Each instruction updates a single lane of the existing destination.
    point=result;
}
Value AttachmentRecovery::RandomPoint(Actor *actor)
{
    Matrix transform;
    Game::Position4 extent;
    if(actor->kind==3) func_00152BB0(actor,&transform,&extent);
    else {
        unsigned long handle=func_001484C8(actor);
        int count=func_0014A650(actor,handle);
        if(count==0) return D_004432A0;
        float total=func_0014A568(actor,handle);
        float limit=func_0012D0D0(0.0f,total,D_0040F4D0),volume=0.0f;
        for(int i=0;i<count && volume<limit;++i) {
            func_0014A6A0(actor,handle,i,&transform,&extent);
            volume+=BoxVolume(extent);
        }
    }
    Value point;
    SetComponent(point,func_0012D0D0(NegativeComponent(extent,0),extent.x,D_0040F4D0),0);
    SetComponent(point,func_0012D0D0(NegativeComponent(extent,1),extent.y,D_0040F4D0),1);
    SetComponent(point,func_0012D0D0(NegativeComponent(extent,2),extent.z,D_0040F4D0),2);
    return Ps2Math::VU0::TransformPoint(transform.row,point);
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B69E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B72E0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B74F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BD8D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BDB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BDEE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BE2A0);
