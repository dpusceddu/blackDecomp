#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: func_00105D48: register allocation and the final configuration store schedule.
#include "game/frontend_resources.hpp"
template<class T> struct FrontendRelative {
    unsigned address;
    T* Relocate(void* base) { address+=(unsigned)base; return (T*)address; }
    T* Get() { return (T*)address; }
};
struct FrontendArchive { int reserved0,reserved4,count; void* entries; };
struct FrontendBinding { char opaque[0x24]; };
struct FrontendBindingList { unsigned char count; char reserved[3]; FrontendRelative<FrontendBinding> entries; };
struct FrontendScenePayload { char reserved[0xa0]; FrontendRelative<void> extra; };
struct FrontendScene {
    int reserved0,reserved4;
    FrontendRelative<FrontendScenePayload> payload;
    FrontendRelative<void> dataC,data10,data14,data18;
    int reserved1c;
};
struct FrontendSceneList { unsigned char reserved0,count; char reserved2[2]; FrontendRelative<FrontendScene> entries; };
struct FrontendArchiveConfig { int reserved0,reserved4; FrontendRelative<void> data8,dataC,data10,data14,data18; };
struct FrontendArchivePackage {
    int version;
    FrontendRelative<FrontendArchive> textures,models;
    FrontendRelative<FrontendBindingList> bindings;
    FrontendRelative<FrontendSceneList> scenes;
    FrontendRelative<FrontendArchiveConfig> config;
    FrontendRelative<void> root;
};
extern "C" FrontendArchivePackage* func_001092F8();
extern "C" void func_00272AA8(void*);
extern "C" void* func_003822E0(void*,int);
extern "C" void* func_003822F8(void*,int);
extern "C" void func_0028EED8(void*);
extern "C" void func_001AF930(void*);
extern "C" void func_00382C70(void*);
extern "C" void* func_001282D0(void*);
extern "C" void func_00108540(void*,int,void*,short);
extern "C" void func_0015CC40(void*,void*);
extern "C" void func_0016BE60(void*);
extern "C" void func_001264C8(void*,void*);
extern "C" void func_00155238(void*);
extern void* D_0040F4C4;
extern void* D_0040F4E0;
extern void* D_0040F4E4;
extern void* D_0040F520;
extern char* D_0040F4D0;
extern char* D_0040F0E0;
extern "C" void func_00105D48() {
    FrontendArchivePackage* package=func_001092F8();
    FrontendArchive* textures=(FrontendArchive*)(package->textures.address+(unsigned)package);
    package->bindings.Relocate(package);
    package->textures.address=(unsigned)textures;
    package->config.Relocate(package);
    package->root.Relocate(package);
    package->scenes.Relocate(package);
    package->models.Relocate(package);
    func_00272AA8(textures);
    for(int index=0;index<textures->count;++index) func_0028EED8(func_003822E0(textures,index));
    FrontendBindingList* bindings=package->bindings.Get();
    bindings->entries.Relocate(bindings);
    for(unsigned index=0;index<bindings->count;++index) func_00382C70(&bindings->entries.Get()[index]);
    FrontendSceneList* scenes=package->scenes.Get();
    scenes->entries.Relocate(scenes);
    for(unsigned char index=0;index<scenes->count;++index) {
        FrontendScene* scene=(FrontendScene*)((index<<5)+(unsigned)scenes->entries.Get());
        FrontendScenePayload* payload=(FrontendScenePayload*)(scene->payload.address+(unsigned)scene);
        scene->dataC.Relocate(scene);
        scene->data10.Relocate(scene);
        void* data14=(void*)(scene->data14.address+(unsigned)scene);
        scene->data18.Relocate(scene);
        scene->data14.address=(unsigned)data14;
        scene->payload.address=(unsigned)payload;
        if(payload->extra.address) payload->extra.Relocate(payload);
    }
    FrontendArchiveConfig* config=package->config.Get();
    config->data8.Relocate(config);
    void* dataC=(void*)(config->dataC.address+(unsigned)config);
    void* data10=(void*)(config->data10.address+(unsigned)config);
    void* data14=(void*)(config->data14.address+(unsigned)config);
    config->dataC.address=(unsigned)dataC;
    config->data10.address=(unsigned)data10;
    config->data14.address=(unsigned)data14;
    config->data18.Relocate(config);
    func_001282D0(package->root.Get());
    func_00108540(D_0040F4C4,0,package->textures.Get(),0);
    FrontendArchive* models=package->models.Get();
    func_00272AA8(models);
    for(int index=0;index<models->count;++index) func_001AF930(func_003822F8(models,index));
    func_00108540(D_0040F4C4,1,package->models.Get(),0);
    func_0015CC40(D_0040F4E0,package->scenes.Get());
    func_0016BE60(D_0040F4D0+0x3f0);
    *(void**)(D_0040F0E0+0x2106c)=package->bindings.Get();
    func_001264C8(D_0040F4E4,package->config.Get());
    func_00155238(D_0040F520);
    void** destination=(void**)(D_0040F4D0+0x5ab8);
    *destination=package->root.Get();
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00105D48);
#endif


#ifdef NON_MATCHING
// Unmatched: func_00106080: switch exit layout and call/store scheduling.
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F544;
extern char* D_0040F4D0;
extern unsigned char* D_0040F504;
extern void** D_0040F4DC;
extern char* D_003BC51C;
extern "C" int func_00128480(void*);
extern "C" int func_0020AD10(void*);
extern "C" void func_00121C38(void*);
extern "C" void func_00122478(void*);
extern "C" void func_00382BD8(void*);
extern "C" void func_001052A0(void*,void*);
extern "C" void* func_001033A0(void*,unsigned char,unsigned char);
extern "C" void func_0020B678(void*,const char*,int);
int FrontendLoadingState::Enter() {
    *(int*)(D_0040F0E0+0x20208)=1;
    switch(state) {
    case 1: case 55:
        state=2;
    case 2: case 28:
        *(unsigned char*)(D_0040F544+0x390f)=1;
        state=3;
    case 3:
        if (func_00128480(D_0040F4D0)) {
        *D_0040F504=0;
        state=4;
    case 4:
        if (func_0020AD10(D_0040F544)) {
        state=5;
    case 5:
        { void** models=D_0040F4DC;
          func_00121C38(*models);
          func_00122478(models);
          func_00382BD8(models); }
        func_001052A0(this,D_0040F0E0+0x21028);
        flags=0;
        state=6;
    case 6:
        state=7;
    case 7:
        specification=func_001033A0(D_0040F0E0,*(unsigned char*)(D_0040F0E0+0x2020c),*(unsigned char*)(D_0040F0E0+0x2020e));
        timeout=3.0f;
        waiting=0;
        forced=0;
        elapsed=0;
        func_0020B678(D_0040F544,D_003BC51C,2);
        state=28;
        return 1;
        }
        }
        return 0;
    default:
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106080);
#endif

#ifdef NON_MATCHING
// Unmatched: func_00106200: clock subobject addressing and flags/virtual-call scheduling.
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F4D0;
extern char* D_0040F510;
extern void* D_0040F524;
extern long** D_0040F4BC;
extern "C" int func_00103870(void*);
extern "C" int func_001063F8(void*);
extern "C" void func_00105228(void*,int);
extern "C" void func_001052A0(void*,void*);
extern "C" void func_00205180(void*);
extern "C" void func_001E8980(int);
void FrontendLoadingState::Update() {
    if (!waiting) {
        long mode=0x6d6123044330fccfL;
        long* current=*D_0040F4BC;
        if(current) mode=*current;
        if(mode==0x594c3b3ed729e1c6L && !func_00103870(D_0040F0E0)) {
            elapsed+=*(float*)(D_0040F4D0+0x1c);
            func_001063F8(this);
        }
    } else {
        struct Clock { char reserved[0x1c]; float delta; };
        Clock* clock=(Clock*)((unsigned int)D_0040F0E0+0x20120);
        timeout-=clock->delta;
        if(timeout<0) {
            if(forced) func_00105228(D_0040F0E0+0x20220,5);
            else func_00105228(D_0040F0E0+0x20220,4);
        }
    }
    if(flags&2) func_001052A0(this,D_0040F0E0+0x2104c);
    else if(flags&1) func_001052A0(this,D_0040F0E0+0x2103c);
    else if(flags&4) {
        if(!request) func_001052A0(this,D_0040F0E0+0x21028);
        else {
            func_001052A0(this,D_0040F0E0+0x21058);
            flags=0;
            goto updateOwner;
        }
    }
    flags=0;
updateOwner:
    func_00205180(D_0040F524);
    func_001E8980(*(int*)(D_0040F510+0xcbd8));
    owner->virtualTable[2].function((char*)owner+owner->virtualTable[2].adjustment);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106200);
#endif


#ifdef NON_MATCHING
// Unmatched: func_00106868: switch exit layout and virtual-call scheduling.
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F544;
extern char* D_0040F4D0;
extern unsigned char* D_0040F504;
extern void** D_0040F4DC;
extern char* D_003BC51C;
extern "C" int func_00128480(void*);
extern "C" int func_0020AD10(void*);
extern "C" void func_00121C38(void*);
extern "C" void func_00122478(void*);
extern "C" void func_00382BD8(void*);
extern "C" void func_00153438(void*);
extern "C" void func_001052A0(void*,void*);
extern "C" void* func_001033A0(void*,unsigned char,unsigned char);
extern "C" void func_0020B678(void*,const char*,int);
int FrontendSequentialLoadingState::Enter() {
    if(state==28) virtualTable[4].function((char*)this+virtualTable[4].adjustment);
    *(int*)(D_0040F0E0+0x20208)=1;
    switch(state) {
    case 1: case 55:
        state=2;
    case 2: case 28:
        *(unsigned char*)(D_0040F544+0x390f)=1;
        state=3;
    case 3:
        if (func_00128480(D_0040F4D0)) {
        state=4;
    case 4:
        if (func_0020AD10(D_0040F544)) {
        state=5;
    case 5:
        *D_0040F504=0;
        { void** models=D_0040F4DC;
          func_00121C38(*models);
          func_00122478(models);
          func_00382BD8(models); }
        func_001052A0(this,D_0040F0E0+0x21028);
        flags=0;
        func_00153438(counter);
        specification=func_001033A0(D_0040F0E0,*(unsigned char*)(D_0040F0E0+0x2020c),*(unsigned char*)(D_0040F0E0+0x2020e));
        timeout=3.0f;
        waiting=0;
        forced=0;
        elapsed=0;
        state=28;
        return 1;
        }
        }
        return 0;
    default:
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00106868);
#endif

#ifdef NON_MATCHING
// Unmatched: func_001069F8: clock subobject addressing and flags/virtual-call scheduling.
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F4D0;
extern char* D_0040F510;
extern void* D_0040F524;
extern long** D_0040F4BC;
extern "C" int func_00103870(void*);
extern "C" int func_00106BF8(void*);
extern "C" void func_00153588(void*);
extern "C" void func_00105228(void*,int);
extern "C" void func_001052A0(void*,void*);
extern "C" void func_00205180(void*);
extern "C" void func_001E8980(int);
void FrontendSequentialLoadingState::Update() {
    if (!waiting) {
        long mode=0x6d6123044330fccfL;
        long* current=*D_0040F4BC;
        if(current) mode=*current;
        if(mode==0x594c3b3ed729e1c6L && !func_00103870(D_0040F0E0)) {
            elapsed+=*(float*)(D_0040F4D0+0x1c);
            func_00153588(counter);
            func_00106BF8(this);
        }
    } else {
        struct Clock { char reserved[0x1c]; float delta; };
        Clock* clock=(Clock*)((unsigned int)D_0040F0E0+0x20120);
        timeout-=clock->delta;
        if(timeout<0) {
            if(forced) func_00105228(D_0040F0E0+0x20220,5);
            else func_00105228(D_0040F0E0+0x20220,4);
        }
    }
    if(flags&2) func_001052A0(this,D_0040F0E0+0x2104c);
    else if(flags&1) func_001052A0(this,D_0040F0E0+0x2103c);
    else if(flags&4) {
        if(!request) func_001052A0(this,D_0040F0E0+0x21028);
        else {
            func_001052A0(this,D_0040F0E0+0x21058);
            flags=0;
            goto updateOwner;
        }
    }
    flags=0;
updateOwner:
    func_00205180(D_0040F524);
    func_001E8980(*(int*)(D_0040F510+0xcbd8));
    owner->virtualTable[2].function((char*)owner+owner->virtualTable[2].adjustment);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001069F8);
#endif


#ifdef NON_MATCHING
// Unmatched: func_00107020: signed-byte loop induction and call scheduling.
#include "game/frontend_resources.hpp"
extern "C" void func_0026C798(void*,int);
extern "C" void func_0026BA20(void*);
extern "C" void func_001246A0(void*,signed char);
extern "C" void func_0026C8D0(void*);
extern "C" void func_0026BFF0(void*);
extern "C" void func_00124708(void*);
extern "C" void func_0026BC50(float,void*);
extern "C" void func_001078F0(void*,int);
extern "C" void func_0020DCB0(void*);
extern "C" void func_0020DCF8(void*,const char*);
extern "C" void func_0020DEC8(void*,const char*);
extern char D_003F2EC0[],D_003F2EE0[];
int FrontendControllerScreen::Enter() {
    switch(state) {
    case 1: case 55:
        func_0026C798(this,0);
        for(signed char i=0;i<2;++i) {
            func_0026BA20(&samples[i]);
            func_001246A0(&channels[i],i);
        }
        state=2;
    case 2:
        func_0026C8D0(this);
        for(signed char i=0;i<2;++i) {
            func_0026BFF0(&samples[i]);
            func_00124708(&channels[i]);
            func_0026BC50(0.05f,&samples[i]);
        }
        for(signed char i=0;i<2;++i) {
            feedback[i]=1; feedback[i+1]=1; feedback[i+2]=1;
        }
        if(feedbackEnabled) func_001078F0(this,0);
        state=3;
    case 3:
        func_0020DCB0(textBox);
        func_0020DCF8(textBox,D_003F2EC0);
        func_0020DEC8(textBox,D_003F2EE0);
        state=28;
    case 28:
    default:
        return 1;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107020);
#endif

#ifdef NON_MATCHING
// Unmatched: func_00107228: controller-state branch layout and register allocation.
#include "game/frontend_resources.hpp"
extern char* D_0040F0E0;
extern char* D_0040F544;
extern "C" void func_0026C8E0();
extern "C" int func_0026BC80(void*);
extern "C" int func_0026C9C0(void*,signed char);
extern "C" void func_0026CA98(void*,void*,signed char);
extern "C" void func_0026CB38(void*,void*,int);
extern "C" int func_00103860();
extern "C" void func_00103800(void*,int);
extern "C" void func_00124728(void*);
extern "C" void func_00124730(void*);
extern "C" void func_00125970(void*);
struct FrontendDisconnectRequest { signed char index; char reserved[7]; unsigned char active; };
struct FrontendStateLink { int state; void* parent; };
void FrontendControllerScreen::Update() {
    func_0026C8E0();
    for(signed char index=0;index<2;++index) {
        FrontendControllerSample* sample=&samples[index];
        int previous=func_0026BC80(sample);
        int current=func_0026C9C0(this,index);
        if(previous==-1 && current==4) func_0026CA98(this,sample,index);
        if(current!=4 && previous!=-1) {
            FrontendDisconnectRequest* request=*(FrontendDisconnectRequest**)(D_0040F0E0+0x21060);
            if(!request) func_0026CB38(this,sample,previous);
            else if(request->active && request->index==index && !func_00103860()) {
                FrontendStateLink* currentState=*(FrontendStateLink**)(D_0040F0E0+0x21070);
                if(currentState==(void*)(D_0040F0E0+0x20f78) || currentState==(void*)(D_0040F0E0+0x20fa0) || currentState==(void*)(D_0040F0E0+0x20fd8)) {
                    int allow=1;
                    if(currentState->parent==D_0040F0E0+0x21028) {
                        if(*(int*)(D_0040F0E0+0x21084) || *(int*)(D_0040F544+0x3924)) allow=0;
                    } else allow=0;
                    func_00103800(D_0040F0E0,allow);
                }
                if(!*(int*)(D_0040F0E0+0x21084)) func_0026CB38(this,sample,previous);
            }
        }
    }
    for(signed char index=0;index<2;++index) {
        func_00124728(&channels[index]);
        func_00124730(&channels[index]);
    }
    func_00125970(this);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107228);
#endif


#ifdef NON_MATCHING
// Unmatched: func_00107470: indexed feedback aliases and float register allocation.
extern char* D_0040F0E0;
struct FrontendControllerFeedback {
    char reserved[0x77c];
    unsigned char enabled;
    unsigned char dirtyPrimary,dirtySecondary;
    char reserved77f;
    float primary,secondary,target;
    float primaryTime,secondaryTime,strength,fadeTime;
    unsigned char enabledGlobal,resetPending[2];
    void Update(signed char index) __asm__("func_00107470");
};
void FrontendControllerFeedback::Update(signed char index) {
    char* bytes=(char*)this;
    FrontendControllerFeedback* lane=(FrontendControllerFeedback*)(bytes+index*4);
    unsigned char* control=(unsigned char*)bytes+index;
    if((lane->primary>0 || lane->secondary>0) && !control[0x77c]) control[0x79d]=1;
    if(control[0x79d]) {
        lane->primary=0; lane->secondary=0; lane->primaryTime=0;
        lane->secondaryTime=0; lane->target=0; lane->strength=0; lane->fadeTime=0;
        control[0x77d]=1; control[0x77e]=1; control[0x79d]=0;
        return;
    }
    if(lane->primaryTime>0) {
        lane->primaryTime-=*(float*)(D_0040F0E0+0x2013c);
        if(lane->primaryTime<=0) { lane->primary=0; control[0x77d]=1; }
        else if(lane->primary!=1) { lane->primary=1; control[0x77d]=1; }
    }
    float value;
    if(lane->secondaryTime>0) {
        lane->secondaryTime-=*(float*)(D_0040F0E0+0x2013c);
        if(lane->secondaryTime<=0) {
            value=lane->target;
            if(lane->secondary!=value) { lane->secondary=value; control[0x77e]=1; }
            lane->strength=0;
            return;
        }
        if(lane->secondaryTime<=lane->fadeTime) {
            value=lane->strength/3.2f;
            if(value<=lane->target) {
                if(lane->secondary!=lane->target) {
                    lane->secondary=lane->target; lane->strength=lane->target; control[0x77e]=1;
                }
            } else if(lane->secondary!=value) {
                lane->secondary=value; lane->strength=value; control[0x77e]=1;
            }
            return;
        }
        value=lane->strength;
    } else value=lane->target;
    if(value!=lane->secondary) { lane->secondary=value; control[0x77e]=1; }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107470);
#endif


#ifdef NON_MATCHING
// Unmatched: func_00106068: store scheduling in the load-state initializer.
// Unmatched: func_001077B8: register allocation of the indexed threshold address.
#ifdef NON_MATCHING
struct FrontendLoadState {
    int state, error;
    char reserved[16];
    long request;
    char reserved20[16];
    void* resource;
    void Reset() __asm__("func_00106068");
};
void FrontendLoadState::Reset() {
    request=0;
    state=1;
    error=0;
    resource=0;
}

struct FrontendControllerThresholds {
    char reserved[0x77c];
    unsigned char enabled[2];
    char reserved77e[14];
    float thresholds[2];
    void Raise(signed char index,int mask,float value) __asm__("func_001077B8");
};
void FrontendControllerThresholds::Raise(signed char index,int mask,float value) {
    if (enabled[index] && (mask&1)) {
        float* threshold=&thresholds[index];
        if (*threshold<value) *threshold=value;
    }
}

#endif
// Unmatched: func_00105BC0: small-data access selection.
// Unmatched: func_00105CF0: argument spill and call scheduling.
// Unmatched: func_001063F8: callee and load-spec return types.
// Unmatched: func_001064D8: callee return and object aliasing.
// Unmatched: func_00106550: unexplained outgoing stack area.
// Unmatched: func_001066D0: callee and load-spec return types.
// Unmatched: func_00106BF8: callee and load-spec return types.
// Unmatched: func_00106CD8: typed status-field register allocation.
// Unmatched: func_00106D70: unexplained outgoing stack area.
// Unmatched: func_00107800: float argument forwarding and threshold layout.
// Unmatched: func_00107880: signed-byte loop induction register allocation.
// Unmatched: func_00107928: callback dispatch and constant ownership.
// Unmatched: func_00107B18: assembler padding of the short wait loop.
// Unmatched: func_00107E30: I/O thread and semaphore callee signatures.
// Unmatched: func_00108120: archive record and callee signatures.
// Unmatched: func_00108218: archive record and callee signatures.
// Unmatched: func_00108540: archive dispatch and cache record types.
// Unmatched: func_00108668: cache cursor and return-register liveness.
// Unmatched: func_001087C8: conditional-return block layout under -G1.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001077B8);
#endif
