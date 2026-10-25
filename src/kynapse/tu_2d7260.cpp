#include "include_asm.h"

#include "kynapse/agents/wander.hpp"
#include "kynapse/predicates.hpp"
// Property and registration names retain the original source-data order.

static inline const char* WanderGraphProperty() {return "Graph";}
struct WanderVirtualEntry {short adjustment;unsigned short reserved;void(*function)();};
struct __attribute__((aligned(8))) WanderRegistrationStorage {unsigned char unverified00[0x110];WanderVirtualEntry* classTable;};
extern "C" {
int func_0035F630();
int func_002E00F0(void*,const char*,Kaim::WanderAgent*(*)(Kaim::BehaviorContext*),int,int,int);
int func_002DFF98(void*,int);
extern int(*D_003C87E0)(void*);
extern WanderRegistrationStorage D_0044F360;
extern WanderVirtualEntry* D_0044F470;
extern WanderVirtualEntry D_003E3BB0[],D_003E2AE0[];
extern Kaim::Vec3 D_004514F8;
extern int D_004512B0;
void* func_002E1C58(void*,void*);
int func_002E0018(void*,void*);
}
namespace Kaim {
struct GraphEntry { int unused; char name[0x80]; void* graph; };
struct GraphRegistry { int unused; GraphEntry** entries;unsigned count;
    int FindId(const char* name) __asm__("func_002F2F58");
};
struct SlotLookup : PolyRoot {
    virtual ~SlotLookup();
    virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual void Slot5();
    virtual bool Lookup(const char*,unsigned*);
};
struct RegistryView {
    GraphRegistry* FindRegistry(ClassInfo*) __asm__("func_002EC058");
    SlotLookup* FindLookup(ClassInfo*) __asm__("func_002EC058");
};
extern RegistryView* gWanderEngine;
extern ClassInfo gTypeRegistryClass,gLookupClass;
struct NavNode {int id;Vec3 position;int unknown10;};
typedef char WanderNodeStride[sizeof(NavNode)==20?1:-1];
typedef char WanderAddressWidth[sizeof(unsigned)==4 && sizeof(void*)==4?1:-1];
struct NodeBank {
 unsigned char unknown00[0xC];unsigned capacity;int unknown10;unsigned liveCount;NavNode* nodes;
 NavNode* NodeAt(unsigned i) {
    if (i>=capacity) return 0;
    // Preserve the byte-offset operand before the PS2 base address.
    unsigned offset=i*sizeof(NavNode);
    NavNode* node=(NavNode*)(offset+(unsigned)nodes);
    return node->id==-1?0:node;
 }
};

WanderAgent* WanderAgent::Create(BehaviorContext* context) { return new WanderAgent(context); }
bool WanderAgent::Update()
{
    bank->ClearActivation();
    if (!pending)
        return false;
    bool ok;
    if (index != 0xffffffffU) {
        FollowQuery query(vector, fieldC, fieldD);
        ok = provider->QueryTransform(&query);
    } else {
        ok = provider->Query(&vector);
    }
    if (ok) {
        bank->Select(provider->id);
        reached = provider->IsActive();
        if (reached) Refresh();
        return true;
    }
    Refresh();
    reached=false;
    return true;
}
}
// This source-data section switch closes Update's unwind range before function alignment.

extern "C" {
void func_002D74A0(int enabled,int phase) {
 if(phase==0xFFFF) {if(enabled!=0) {func_002E00F0(&D_0044F360,"CWanderAgent",&Kaim::WanderAgent::Create,0,0,0);return;}D_0044F470=D_003E2AE0;}
}
}
namespace Kaim {
WanderAgent::WanderAgent(BehaviorContext* c):Behavior(c),index(0xffffffffU),fieldC(0x7fffffff),fieldD(0xffffffffU) { pending=0;provider=0; }
}
// The destruction return contract remains unverified; observed base/free calls are retained.
extern "C" int func_002D7558(void* self,int flags) {
 *(WanderVirtualEntry**)self=D_003E3BB0;
 int result=func_002DFF98(self,0);
 if(flags&1)result=D_003C87E0(self);
 return result;
}
namespace Kaim {
bool WanderAgent::Configure(ChildBuffers* property) {
    if(!property)return false;
    if(!_stricmp(property->GetSecond(),WanderGraphProperty())) {
        const char* name=property->GetValue();
        if(name) {
            GraphRegistry* registry=gWanderEngine->FindRegistry(&gTypeRegistryClass);
            if(!registry)return false;
            int id=registry->FindId(name);
            if(!id)return false;
            SetType(id);
            return true;
        }
    }
    return Ps2Math::Kynapse::IsPrivateProperty(property);
}
}
bool IsSet24::IsSet() const {if(value!=0)return true;return false;}
extern "C" int func_002D76A0(Kaim::WanderAgent* self,void* config) {
 self->vector=D_004514F8;
 self->reached=false;
 self->fieldC=0x7FFFFFFF;
 void* found=func_002E1C58(self->context,&D_004512B0);
 self->pending=0;
 self->provider=(Kaim::TargetEntity*)found;
 if(func_002E0018(self,config)==0)return 0;
 char* table=*(char**)self;
 return (*(int (**)(void*))(table+0x44))((char*)self+*(short*)(table+0x40))!=0;
}
namespace Kaim {
bool WanderAgent::Start() {
    if(!pending)return false;
    if(fieldC==0x7fffffff)Refresh();
    return true;
}
void WanderAgent::Pick() {
 unsigned draw=(unsigned)func_0035F630();
 NodeBank* bank=(NodeBank*)pending;
 unsigned ordinal=draw%bank->liveCount;
 fieldD=index;
 fieldC=ordinal;
 NavNode* node=bank->NodeAt(ordinal);
 vector=node->position;
}
void WanderAgent::SetType(int id) {
    pending=(void*)id;
    index=0xffffffffU;
    GraphRegistry* registry=gWanderEngine->FindRegistry(&gTypeRegistryClass);
    if(registry) {
        SlotLookup* lookup=gWanderEngine->FindLookup(&gLookupClass);
        if(lookup)for(unsigned i=0;i<registry->count;++i) {
            if(registry->entries[i]->graph==pending) {
                if(!lookup->Lookup(registry->entries[i]->name,&index))index=0xffffffffU;
                return;
            }
        }
    }
}
}

// Virtual-entry layout is verified; unused slot identities remain unknown.
extern "C" {
void func_003897C8();int func_002D7558(void*,int);int func_002D76A0(Kaim::WanderAgent*,void*);void func_002D75B0();
void func_0038BB28();void func_00389818();void func_002D7748();void func_002D7308();
void func_002D7690();void func_002D77A0();
WanderVirtualEntry Wander_VirtualEntries[11] __attribute__((section(".data.wander_vtable"),aligned(8))) = {
 {0,0,func_003897C8},{0,0,(void (*)())func_002D7558},{0,0,(void (*)())func_002D76A0},{0,0,func_002D75B0},
 {0,0,func_0038BB28},{0,0,func_00389818},{0,0,func_002D7748},{0,0,func_002D7308},
 {0,0,func_002D7690},{0,0,func_002D77A0},{0,0,0}
};
}

// Original image labels alias this registration storage, including its table pointer.
extern "C" {WanderRegistrationStorage Wander_RegistrationStorage __attribute__((aligned(8)));}
extern "C" {
void func_002D7930() {func_002D74A0(1,0xFFFF);}
void func_002D7950() {func_002D74A0(0,0xFFFF);}
}
